
const http = require("http");
const { spawn } = require("child_process");
const readline = require("readline");
const path = require("path");

// Project root
const projectRoot = path.resolve(__dirname, "..");

// C++ executable
const executable = path.join(
    projectRoot,
    "build",
    "bin",
    process.platform === "win32" ? "CakeQuest.exe" : "CakeQuest"
);

// Recipe dataset
const dataset = path.join(
    projectRoot,
    "data",
    "cleaned",
    "200k.json"
);

console.log("Starting C++ backend...");

// Launch C++ once and keep it running.
const backend = spawn(executable, [dataset], {
    cwd: projectRoot,
    stdio: ["pipe", "pipe", "inherit"]
});

// Read JSON responses from C++.
const output = readline.createInterface({
    input: backend.stdout
});

// Keep track of requests waiting for responses.
const pendingRequests = [];

output.on("line", (line) => {
    const pending = pendingRequests.shift();

    if (!pending) {
        console.error("Unexpected backend output:", line);
        return;
    }

    try {
        pending.resolve(JSON.parse(line));
    } catch (error) {
        pending.reject(error);
    }
});

backend.on("error", (error) => {
    console.error("Could not start C++ backend:", error.message);
});

backend.on("close", (code) => {
    console.log("C++ backend stopped with code:", code);

    while (pendingRequests.length > 0) {
        pendingRequests.shift().reject(
            new Error("C++ backend stopped.")
        );
    }
});

// Send a search request to C++.
function searchBackend(ingredients, allIngredients, searchMethod) {
    return new Promise((resolve, reject) => {

        pendingRequests.push({ resolve, reject });

        backend.stdin.write(
            JSON.stringify({
                ingredients,
                allIngredients,
                searchMethod
            }) + "\n",
            (error) => {
                if (error) {
                    const pending = pendingRequests.pop();

                    if (pending) {
                        pending.reject(error);
                    }
                }
            }
        );
    });
}

// HTTP server
const server = http.createServer(async (req, res) => {

    res.setHeader("Access-Control-Allow-Origin", "http://localhost:5173");
    res.setHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
    res.setHeader("Access-Control-Allow-Headers", "Content-Type");

    if (req.method === "OPTIONS") {
        res.writeHead(204);
        res.end();
        return;
    }

    if (req.method !== "POST" || req.url !== "/api/search") {
        res.writeHead(404);
        res.end(JSON.stringify({ error: "Not found" }));
        return;
    }

    try {
        let body = "";

        for await (const chunk of req) {
            body += chunk;

            if (body.length > 100000) {
                res.writeHead(413);
                res.end(JSON.stringify({ error: "Request too large" }));
                return;
            }
        }

        const request = JSON.parse(body);

        if (
            !Array.isArray(request.ingredients) ||
            request.ingredients.length === 0 ||
            !request.ingredients.every(
                item => typeof item === "string" && item.trim().length > 0
            )
        ) {
            res.writeHead(400);
            res.end(JSON.stringify({
                error: "Please provide a list of ingredients."
            }));
            return;
        }

        // Read frontend search selections
        const searchMethod = request.searchMethod || "btree";
        const allIngredients = request.allIngredients === true;

        if (!["btree", "hash"].includes(searchMethod)) {
            res.writeHead(400);
            res.end(JSON.stringify({
                error: "Invalid search method."
            }));
            return;
        }

        const results = await searchBackend(
            request.ingredients.map(item => item.trim()),
            allIngredients,
            searchMethod
        );

        res.writeHead(200, {
            "Content-Type": "application/json"
        });

        res.end(JSON.stringify(results));

    } catch (error) {
        console.error("Search error:", error);

        res.writeHead(500, {
            "Content-Type": "application/json"
        });

        res.end(JSON.stringify({
            error: "Search failed."
        }));
    }
});

server.listen(3001, () => {
    console.log("CakeQuest backend listening on port 3001");
});
