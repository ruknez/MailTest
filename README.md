# MailTest

Реализованная программа производит скачивание данных по переданному URL.
Для компиляции программы необходим компилятор gcc-8 и выше версии.

Что бы запустить сборку программы необходимо выполнить команду bash startAssembly.sh
Если необходимо указать путь к компилятору используется -DCMAKE_CXX_COMPILER:STRING=<путь>

Для тестирования приложения использовался boost test что бы включить сборку
тестов -DBUILD_TESTS=ON

Пример запуска сборки:  bash startAssembly.sh -DCMAKE_CXX_COMPILER:STRING=/usr/bin/g++-8 -DBUILD_TESTS=ON

Также в проек интегрирована порадигма CI/CD
Успешные сборки: https://travis-ci.org/ruknez/MailTest/builds
Результат сборки: https://bintray.com/ruknez/MailTestTask/Get#files


