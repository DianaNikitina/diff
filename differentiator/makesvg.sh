for file in dot_files/*.dot; do

    filename=$(basename "$file" .dot)

    dot "$file" -T svg -o "images/${filename}.svg"

done

echo -e "Converted dot_files/*.dot files to images/*.svg\n"