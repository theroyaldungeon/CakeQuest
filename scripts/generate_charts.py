import csv
import sys
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib import font_manager

ROOT = Path(__file__).resolve().parent.parent
DEFAULT_CSV = ROOT / "results" / "benchmark_results.csv"
DEFAULT_OUT = ROOT / "frontend" / "src" / "assets" / "charts"

SURFACE = "#FFF0F4"
INK = "#343434"
INK_MUTED = "#6b5b60"
GRID = "#e6d3d9"
COLORS = {"btree": "#2a78d6", "hash": "#eb6834"}
NAMES = {"btree": "B-tree", "hash": "Hash index"}
MARKERS = {"btree": "o", "hash": "s"}
ORDER = ("btree", "hash")


def load(path):
    data = {}
    with open(path, newline="") as f:
        for row in csv.DictReader(f):
            key = (row["category"], row["structure"])
            data.setdefault(key, []).append((int(row["data_size"]), float(row["value"])))
    for pts in data.values():
        pts.sort()
    return data


def size_label(n):
    return f"{n // 1000}k"


def setup_style():
    available = {f.name for f in font_manager.fontManager.ttflist}
    family = "Space Mono" if "Space Mono" in available else "DejaVu Sans Mono"
    plt.rcParams.update({
        "font.family": family,
        "text.color": INK,
        "axes.labelcolor": INK_MUTED,
        "xtick.color": INK_MUTED,
        "ytick.color": INK_MUTED,
        "figure.facecolor": SURFACE,
        "axes.facecolor": SURFACE,
        "savefig.facecolor": SURFACE,
    })


def style_axes(ax, sizes, ymax, ylabel=None):
    for side in ("top", "right", "left"):
        ax.spines[side].set_visible(False)
    ax.spines["bottom"].set_color(GRID)
    ax.grid(axis="y", color=GRID, linewidth=1)
    ax.set_axisbelow(True)
    ax.tick_params(length=0, labelsize=9)
    ax.set_xticks(sizes)
    ax.set_xticklabels([size_label(s) for s in sizes])
    ax.set_xlim(min(sizes) - 0.04 * max(sizes), max(sizes) * 1.42)
    ax.set_ylim(0, ymax * 1.30)
    ax.set_xlabel("Recipes indexed", fontsize=9)
    if ylabel:
        ax.set_ylabel(ylabel, fontsize=9)


def max_value(data, categories, scale):
    return max(v * scale for c in categories for s in ORDER for _, v in data[(c, s)])


def draw(ax, data, category, scale, value_fmt):

    for s in ORDER:
        pts = data[(category, s)]
        xs = [p[0] for p in pts]
        ys = [p[1] * scale for p in pts]
        ax.plot(xs, ys, color=COLORS[s], linewidth=2, marker=MARKERS[s], markersize=7,
                markeredgecolor=SURFACE, markeredgewidth=2, label=NAMES[s], zorder=3)
        ax.annotate(f"{NAMES[s]}\n{value_fmt.format(ys[-1])}", (xs[-1], ys[-1]),
                    xytext=(10, 0), textcoords="offset points", va="center",
                    fontsize=9, color=INK)


def make_chart(data, category, scale, value_fmt, title, subtitle, ylabel, out_file):
    sizes = [p[0] for p in data[(category, "btree")]]
    fig, ax = plt.subplots(figsize=(8, 4.6))
    draw(ax, data, category, scale, value_fmt)
    style_axes(ax, sizes, max_value(data, [category], scale), ylabel)
    ax.legend(frameon=False, loc="upper left", fontsize=9, labelcolor=INK)
    fig.suptitle(title, x=0.02, y=0.98, ha="left", fontsize=14, fontweight="bold", color=INK)
    fig.text(0.02, 0.905, subtitle, ha="left", fontsize=9, color=INK_MUTED)
    fig.tight_layout(rect=(0, 0, 1, 0.90))
    fig.savefig(out_file, dpi=200)
    plt.close(fig)


def make_lookup_chart(data, out_file):
    sizes = [p[0] for p in data[("lookup_hit_ns", "btree")]]
    ymax = max_value(data, ["lookup_hit_ns", "lookup_miss_ns"], 1)
    fig, (ax_hit, ax_miss) = plt.subplots(1, 2, figsize=(10, 4.6), sharey=True)
    for ax, cat, label in ((ax_hit, "lookup_hit_ns", "Hit: ingredient exists"),
                           (ax_miss, "lookup_miss_ns", "Miss: ingredient not found")):
        draw(ax, data, cat, 1, "{:.0f} ns")
        style_axes(ax, sizes, ymax, "Time per lookup (ns)" if ax is ax_hit else None)
        ax.set_title(label, loc="left", fontsize=10, color=INK)
    ax_hit.legend(frameon=False, loc="upper left", fontsize=9, labelcolor=INK)
    fig.suptitle("Lookup time per search() call", x=0.02, y=0.98, ha="left",
                 fontsize=14, fontweight="bold", color=INK)
    fig.text(0.02, 0.905, "Median of repeated runs, lower is better", ha="left",
             fontsize=9, color=INK_MUTED)
    fig.tight_layout(rect=(0, 0, 1, 0.90))
    fig.savefig(out_file, dpi=200)
    plt.close(fig)


def main():
    csv_path = Path(sys.argv[1]) if len(sys.argv) > 1 else DEFAULT_CSV
    out_dir = Path(sys.argv[2]) if len(sys.argv) > 2 else DEFAULT_OUT
    if not csv_path.exists():
        sys.exit(f"Could not find {csv_path}\nRun the benchmark first to create it.")
    out_dir.mkdir(parents=True, exist_ok=True)

    setup_style()
    data = load(csv_path)

    make_chart(data, "build_ms", 1, "{:.1f} ms",
               "Index build time", "Median of repeated builds, lower is better",
               "Build time (ms)", out_dir / "build_time.png")
    make_lookup_chart(data, out_dir / "lookup_time.png")
    make_chart(data, "memory_bytes", 1 / 1e6, "{:.1f} MB",
               "Index memory usage", "Heap bytes allocated by the index, lower is better",
               "Memory (MB)", out_dir / "memory_usage.png")

    print(f"Read  {csv_path}")
    print(f"Wrote build_time.png, lookup_time.png, memory_usage.png to {out_dir}")


if __name__ == "__main__":
    main()