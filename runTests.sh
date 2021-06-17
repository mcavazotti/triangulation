make
for file in testes/*
do
    echo
    echo "testing $file"
    ./triangulate < "$file" | python3 draw_lines.py
done