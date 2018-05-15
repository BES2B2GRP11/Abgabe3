# Abgabe3
Abgabe zum Beispiel 3 Gruppe 11 BES 2B2 

## nur sender oder empfänger bauen
im **src** folder kann man **make s** bzw **make e** respektive abfeuern

## Libaries
Für den Ringbuffer wurde eine statische library vorbereitet
**ring_buffer.{c,h}**.

Für alles was im shared-memory erstellt, verwaltet und gelöscht wird, wurde eine
weitere statische library **sharedmem** vorbereitet. 
 
## Semaphore und shared memory bits

Aus der Angabe: 

>>Führen Sie die Synchronisation mittels Semaphoren durch. Definieren Sie hierzu
>>die Namen von Shared Memory und Semaphoren in einem gemeinsamen Headerfile,
>>welches sowohl von sender als auch von empfaenger verwendet wird. Um zu
>>verhindern, daß andere Studierende die selben Namen verwenden wie Sie selbst,
>>verwenden Sie bitte folgendes Namensschema:
>>
>>
>>    name0 = "/shm_{1000 * <uid> + 0}"
>>
>>    name1 = "/shm_{1000 * <uid> + 1}"
>>
>>    name2 = "/sem_{1000 * <uid> + 2}"
>>
>>    ...
>>
>>    nameX = "/sem_{1000 * <uid> + X}"
>>
>>    
>>Hierbei soll <uid> Ihre eigene user ID sein, welche Sie durch Aufruf von id(1)
>>auf der Kommandozeile bzw. getuid(2) aus Ihrem Programm heraus ermitteln können.

**ring_buffer** und **sharedmem** library haben jeweils ihre eigenen semaphore
und Behandlung dieser.
