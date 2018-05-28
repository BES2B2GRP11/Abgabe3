# Abgabe3
Abgabe zum Beispiel 3 Gruppe 11 BES 2B2 

## nur sender oder empfänger bauen
im **src** folder kann man **make s** bzw **make e** respektive abfeuern

## Libaries

 * **libringbuffer.a** aus __ringbuffer.{c,h}__ Alles was den Ringbuffer angeht
 * **libsharedmem.a**  aus __sharedmem.{c,h}__  Alles was /dev/shm angeht 
 * **libsemaphores.a** aus __semaphores.{c,h}__ Alles was semaphore angeht
 
## Semaphore und shared memory bits

Aus der Angabe: 

>Führen Sie die Synchronisation mittels Semaphoren durch. Definieren Sie hierzu
>die Namen von Shared Memory und Semaphoren in einem gemeinsamen Headerfile,
>welches sowohl von sender als auch von empfaenger verwendet wird. Um zu
>verhindern, daß andere Studierende die selben Namen verwenden wie Sie selbst,
>verwenden Sie bitte folgendes Namensschema:
>
>
>    name0 = "/shm_{1000 * \<uid\> + 0}"
>
>    name1 = "/shm_{1000 * \<uid\> + 1}"
>
>    name2 = "/sem_{1000 * \<uid\> + 2}"
>
>    ...
>
>    nameX = "/sem_{1000 * \<uid\> + X}"
>
>    
>Hierbei soll <uid> Ihre eigene user ID sein, welche Sie durch Aufruf von id(1)
>auf der Kommandozeile bzw. getuid(2) aus Ihrem Programm heraus ermitteln können.

Wird brauchen ein complex bzw ein counting und binary semaphore. Counting sagt an wie viele Prozesse noch mit dem Buffer arbeiten,
und der Binary gibt an, ob der Buffer gerade fuer eine Lese- oder Schreiboperation verfuegbar ist.

Wir sollen semaphore ohne busy-waiting verwenden. 

## Links
[Gute Ressource zum Ring-Buffer Clicke hier :D](https://embedjournal.com/implementing-circular-buffer-embedded-c/ "Embedded FTW")

Anleitungsvideo leider ohne Sound aber mit viel Text :)

[![IMAGE ALT TEXT
HERE](http://img.youtube.com/vi/2--Z-iC2EYk/0.jpg)](http://www.youtube.com/watch?v=2--Z-iC2EYk)

## Hier eine Uebersicht:

```
                         +----------------------------------------------------------------------------------+
                         |  [Datei mit n fixen Bloecken in /dev/shm als circular-linked-list] == ringbuffer |
                         |  Ist fuer beide Programme gleich /dev/shm/shm_{1000*uid+0}                       |
                         |                                                                                  |
                         |       1      2      3      4      5      6                                   n   |
                         |     +---+  +---+  +---+  +---+  +---+  +---+                               +---+ |
                         |     |   |  |   |  |   |  |   |  |   |  |   |                               |   | |
                         +---> |   +> |   +> |   +> |   +> |   +> |   +--------> . . . . . . . +----> |   +-+
                               +-+-+  +-+-+  +-+-+  +-+-+  +-+-+  +-+-+                               +-+-+
                                 ^      ^      ^      ^      ^      ^                                   ^
                                 |      |      |      |      |      |                                   |
                                 |      |      |      |      |      |                                   |
                                 +      +      +      +      +      +                                   +
                                 p      p      p      p      p      p                                   p

                               +----------------------------------------------------------+------------------+
                               |                                                          |                  |
                               |  [Datei mit n fixen blöcken]+>/dev/shm/shm_{1000*uid+j}  |  /dev/shm @ RAM  |
                               |                                                          |                  |
                               +------------+-+-------------------------------------------+------------------+
                                            ^ ^
                                            | |
+-----------------------------+             | |                                  +------------------------------+
|   Sender                    |             | |                                  |                    Empfaenger|
+-----------------------------+             | |                                  +------------------------------+
|                             |             | |                                  |                              |
| int fd = /dev/shm/shm_...   |             | |                                  |  int fd = /dev/shm/shm_...   |
|                             +-------------+ +----------------------------------+                              |
| Complex+Semaphore+up()      |                                                  |  Complex+Semaphore+up()      |
|                             | Alle Arbeiten mit den gleichen Dateien.          |                              |
| write to ringbuffer@dev/shm | Bei uns macht es die Reihenfolge:                |  read from ringbuffer@dev/shm|
|                             |                                                  |                              |
| Complex+Semaphore+down()    | /dev/shm_{1000*uid+j} -> j = 0 ==> ringbuffer    |  Complex+Semaphore+down()    |
|                             |                                                  |                              |
| atexit(cleanup)             | Fuer Semaphore:                                  |  atexit(cleanup)             |
+-----------------------------+ /dev/sem_{1000*uid+j} -> j = 0 --> complex-sem.  +------------------------------+
                                /dev/sem_{1000*uid+j} -> j = 1 --> ring buffer sem

                                Der Complex-Semaphore gibt an, wie viele threads
                                bzw. Prozesse sich in der geschuetzten Region befinden.
                                Diese wird ausgewertet beim Abbau und Loeschen des Buffers:
                                Empfaenger ist der letzte, der noch mit dem buffer arbeitet,
                                somit kann er nach dem letzten auslesen auch geloescht werden.

                                Der Ring buffer Semaphore wird verwendet um das Lesen und Schreiben
                                in dem Ringbuffer zu Synchronisieren.

```