#!/usr/bin/env bash
set -euo pipefail

if [ $# -lt 1 ]; then
  echo "Usage: $0 /path/to/binary"
  exit 1
fi

BINARY="$1"
OUTPUT_DIR="data/output"
TMP_DIR="$OUTPUT_DIR/tmp_dumps"
OUTPUT_FILE="$OUTPUT_DIR/matrix_dump.bin"

# Параметры матрицы
ROWS=4      # число строк
COLS=4      # число столбцов
ESIZE=8     # размер одного элемента в байтах

# Проверка бинарника
if [ ! -x "$BINARY" ]; then
  echo "Error: '$BINARY' не найден или не исполняемый."
  exit 2
fi

# Подготовка директорий
rm -rf "$TMP_DIR"
mkdir -p "$TMP_DIR" "$OUTPUT_DIR"
rm -f "$OUTPUT_FILE"

# Собираем аргументы для gdb
gdb_args=(
  -batch
  -ex "file $BINARY"
  -ex "break 11"
  -ex "run"
  -ex "next"
  -ex "set pagination off"
)

# Для каждой строки выполняем dump memory
for (( iter=0; iter<ROWS; iter++ )); do
  length=$(( COLS * ESIZE ))
  gdb_args+=(
    -ex "dump memory $TMP_DIR/row_${iter}.bin \
      (char*)matrix.matrix->data[${iter}] \
      ((char*)matrix.matrix->data[${iter}] + ${length})"
  )
done

gdb_args+=( -ex "quit" )

# Запуск gdb
echo "Running gdb dump..."
gdb "${gdb_args[@]}"

# Склеиваем бинарные файлы строк в один файл
for (( iter=0; iter<ROWS; iter++ )); do
  cat "$TMP_DIR/row_${iter}.bin" >> "$OUTPUT_FILE"
done

# Удаляем временные дампы
rm -rf "$TMP_DIR"

echo "✔ Matrix dump saved to: $OUTPUT_FILE"
