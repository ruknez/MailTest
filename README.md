# MailTest

Реализованная программа производит скачивание данных по переданному URL.
Для компиляции программы необходим компилятор gcc-8 и выше версии.

Что бы запустить сборку программы необходимо выполнить команду bash startAssembly.sh
Если необходимо указать путь к компилятору используется -DCMAKE_CXX_COMPILER:STRING=<путь>

Для тестирования приложения использовался boost test что бы включить сборку
тестов -DBUILD_TESTS=ON

Пример запуска сборки:  bash startAssembly.sh -DCMAKE_CXX_COMPILER:STRING=/usr/bin/g++-8 -DBUILD_TESTS=ON

Также в проект интегрирована парадигма CI/CD
Успешные сборки: https://travis-ci.org/ruknez/MailTest/builds
Результат сборки: https://bintray.com/ruknez/MailTestTask/Get#files

Програмное средство тестировалось на следующих URL

https://download.geofabrik.de/russia/central-fed-district-latest.osm.pbf
http://code.jquery.com/jquery-1.11.1.js
https://download.geofabrik.de/russia.html
http://bbgentoo.ilb.ru/distfiles/google-chrome-stable_48.0.2564.116-1_i386.deb


