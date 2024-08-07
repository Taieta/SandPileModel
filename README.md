# Abelian sandpile model simulation

Изначальное состояние задается входным файлом.

Размер сетки может изменяться в процессе работы программы.

Реализация - консольное приложение, поддерживающее следующие аргументы командной строки:

  **-i, --input**    - [tsv-файл](https://en.wikipedia.org/wiki/Tab-separated_values) (tab-separated values) c начальными данными

  **-o, --output**   - путь к директории для сохранения картинок

  **-m, --max-iter** - максимальное количество итераций модели

  **-f, --freq**     - частота, с которой должны сохранятся картинки (если 0, то сохраняется только последнее состояние)

Формат файла:
Каждая строчка содержит информацию об одной ячейке, в виде (x-координаты, y-координаты, количество песчинок), разделенных символом табуляции. Количество песчинок гарантированно влезет в `uint64_t`, координаты гарантированно влезают в `int16_t`

## Примечания к модели

1. Новые песчинки добавляются только при инициализации.

2. Состояние следующего поколения ячеек зависит только от предыдущего состояния сетки.

3. Цвета песчинок при каждом отрисовывании выбираются случайно.
