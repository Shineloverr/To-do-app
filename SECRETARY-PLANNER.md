﻿

## ТРЕБОВАНИЯ К ПРОЕКТУ

## Содержание
1.  Введение
    1.1.  Назначение
    1.2.  Бизнес-требования
    1.2.1.  Границы проекта
    1.3  Аналоги
    
2.  Требования пользователя
    2.1.  Программные интерфейсы
    2.2.  Интерфейс пользователя
    2.3.  Характеристики пользователей

    
 -  Системные требования
    3.1.  Функциональные требования
    3.2.  Нефункциональные требования 
    3.2.1.  Атрибуты качества 
    3.2.2.  Внешний интерфейс
    


    ## **1. Введение
    **1.1 Назначение****
    В современном мире многозадачность человека быстро растет, увеличивается необходимость запоминания большого количества информации, правильного распределения времени.
    Секретарь-планировщик — это специальная программа, с помощью которой пользователь может планировать свой день, структурировать поставленные задачи и выполнять их вовремя. За счет сортировки и поступления уведомлений о необходимости начала, повышается эффективность выполнения задач пользователя, исключается пропуск важных вопросов из-за забывчивости.
    
    **1.2 Бизнес - требования
     1.2.1. Границы проекта**
     
     Программа "Секретарь-планировщик" рассчитана в основном на студентов, которые вследствие обширной учебной программы в высшем учебном заведении не успевают или же забывают некоторые поставленные в университете задачи. С помощью этой программы время можно с лёгкостью оптимизировать, а также нужда в запоминании большого количества самых разнообразных дел отпадает - ведь весь список дел можно просмотреть в приложении.
     
     **1.3 Аналоги**
     
     Аналогами данного приложения являются: Trello — облачная программа для управления проектами небольших групп, разработанная Fog Creek Software; Todoist — набор программного обеспечения для управления задачами; Evernote — набор программного обеспечения для создания и хранения заметок. Представленные аналоги обладают более высоким функционалом, однако разработанное приложение предоставляет пользователю удобный минималистичный интерфейс, который упрощает использование приложения.

    ## **2. Требования пользователя**
    **2.1 Программные интерфейсы**
    
    
    Работа программы разделена на три основных этапа: загрузка данных из файлов и инициализация объектов, необходимых для работы программы, взаимодействие с пользователем с помощью графического интерфейса, запись данных в файлы при завершении работы программы.
    Была использована среда разработки QtCreator 4.10.0 и операционная система Windows 10.
    
    **2.2 Интерфейс пользователя**

    Блок графического интерфейса является основным в работе приложения, так как соединяет все блоки, предназначенные для взаимодействия с пользователем, между собой, предоставляет пользователю доступ к функционалу приложения. Графический интерфейс данного приложения представляет собой панель задач, которая постоянно отображается в основном окне приложения, два центральных виджета, отображаемых по выбору пользователя, и одно независимое окно.
Также отдельным блоком можно считать часть программы, отвечающую за отмену последнего действия, которой необходимо взаимодействовать со всеми остальными частями программы.

     **2.3 Характеристики пользователей**

    Целевой аудиторией этого приложения являются люди, которые постоянно перегружены различными задачами и целями на день. Оптимизация времени и структурирование бытовых\каждодневных задач - важнейшие цели при создании приложения.

    ##  **3.  Системные требования**
    -Операционная система Windows 98, XP, Vista,7, 8.1, 10;
-Процессор Intel Pentium III 1 GHz;
-Оперативная память 500 MB;
-Свободное место на жестком диске: 5 Мб;

    **3.1 Функциональные требования**

    Пользователю предоставлены возможности, представленные в таблице.
    
             |функция                | требование 
             |Создание листа         |Приложение должно предоставить возможность создания листа для новых заданий
             |Удаление листа         |Приложение должно предоставить возможность удаления листа для новых заданий
             |Включение уведомлений* |Приложение должно предоставить возможность включения уведомлений в фоновом режиме работы приложения
             |Выключение уведомлений*|Приложение должно предоставить возможность выключения уведомлений в активном режиме работы приложения    
             |Редактирование листа   |Приложение должно предоставить возможность внесения правок в уже существующий лист
             |Создание задачи        |Приложение должно предоставить возможность создания задачи в уже существующем листе
             |Удаление задачи        |Приложение должно предоставить возможность удаления уже существующей задачи в уже существующем листе

     **3.2 Нефункциональные требования**
     **3.2.1.  Атрибуты качества**
     

    - минималистичный и интуитивно понятный интерфейс
    - оптимизация приложения под разные OC
    

 

     


                   
 





