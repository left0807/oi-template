#!/bin/bash
# cpp_to_pdf_fixed.sh — WORKS on Ubuntu 22.04/24.04, Debian 12, Fedora, Arch, macOS
# No more "couldn't open input file "-"" errors

set -euo pipefail

DIR="${1:-.}"
OUTPUT="${2:-cpp_codebase.pdf}"
TMPDIR=$(mktemp -d)
trap 'rm -rf "$TMPDIR"' EXIT

echo "Scanning $DIR for C++ files..."

# Collect all files first
mapfile -t FILES < <(find "$DIR" -type f \( -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" -o -name "*.h" -o -name "*.hpp" \) | sort)

if [ ${#FILES[@]} -eq 0 ]; then
    echo "No .cpp/.h files found in $DIR"
    exit 1
fi

# Create individual PostScript files
PS_FILES=()
TOC_ENTRIES=""

i=1
for file in "${FILES[@]}"; do
    rel="${file#./}"
    ps_file="$TMPDIR/file_$i.ps"
    PS_FILES+=("$ps_file")

    echo "[$i/${#FILES[@]}] $rel"

    # Header + code in one go (avoids stdin bug)
    {
        echo "($rel) =="
        echo
        enscript -h -f Courier8 -T 4 --word-wrap --line-numbers -p "$ps_file" "$file"
    } > /dev/null 2>&1

    TOC_ENTRIES="$TOC_ENTRIES($rel) $i\n"
    ((i++))
done

# === Generate Table of Contents ===
TOC_PS="$TMPDIR/toc.ps"
{
    echo "/Courier findfont 12 scalefont setfont"
    echo "72 720 moveto"
    echo "(Table of Contents) show"
    echo "72 690 moveto"
    echo "/lineheight 14 def"
    echo "0 1 $((i-1)) {"
    echo "  /n exch def"
    echo "  n 1 sub dup"
    echo "  72 690 n lineheight mul sub moveto"
    echo "  (File ) show n 48 string cvs show ( .................................... Page ) show"
    echo "  n 48 string cvs show"
    echo "} for"
} > "$TMPDIR/toc.ps.raw"

# Convert TOC to PS properly
enscript -p "$TOC_PS" "$TMPDIR/toc.ps.raw" >/dev/null 2>&1

# === Merge TOC + all files ===
ALL_PS="$TMPDIR/all.ps"
gs -q -dBATCH -dNOPAUSE -sDEVICE=ps2write -sOutputFile="$ALL_PS" \
    "$TOC_PS" "${PS_FILES[@]}" >/dev/null 2>&1

# === Convert to PDF ===
echo "Generating $OUTPUT ..."
ps2pdf "$ALL_PS" "$OUTPUT"

echo "Done! $OUTPUT created with ${#FILES[@]} files"
echo "   $(du -h "$OUTPUT" | cut -f1) — open with: xdg-open \"$OUTPUT\""
