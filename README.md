## Описание
Это консольное c++ приложение для применения различных фильтров к изображению формата bmp

#### Crop (-crop width height)
    Обрезает изображение до заданных ширины и высоты. Используется верхняя левая часть изображения.

    Если запрошенные ширина или высота превышают размеры исходного изображения, выдается доступная часть изображения.

#### Grayscale (-gs)
    Преобразует изображение в оттенки серого по формуле

#### Negative (-neg)
    Преобразует изображение в негатив по формуле

#### Sharpening (-sharp)
    Повышение резкости. Достигается применением матрицы

#### Edge Detection (-edge threshold)
    Выделение границ. Изображение переводится в оттенки серого и применяется матрица

    Пиксели со значением, превысившим `threshold`, окрашиваются в белый, остальные – в черный.

#### Gaussian Blur (-blur sigma)
    Размывает изображение с заданныи параметром sigma.

#### Genius (-genius threshold)
    Выделяет контуры изображения в соответствии с параметром threshold
    
    Заменяет каждый пиксель на медеанный для уменьшения количества цветов в изображении

## Формат аргументов командной строки

Описание формата аргументов командной строки:

`{имя программы} {путь к входному файлу} {путь к выходному файлу}
[-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...]
[-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ...`

При запуске без аргументов программа выводит справку.

### Пример
`./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5`

В этом примере
1. Загружается изображение из файла `input.bmp`
2. Обрезается до изображения с началом в верхнем левом углу и размером 800х600 пикселей
3. Переводится в оттенки серого
4. Применяется размытие с сигмой 0.5
5. Полученное изображение сохраняется в файл `/tmp/output.bmp`

Список фильтров может быть пуст, тогда изображение должно быть сохранено в неизменном виде.
Фильтры применяются в том порядке, в котором они перечислены в аргументах командной строки.

