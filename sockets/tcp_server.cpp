/*
 * tcp_server.c
 * 
 * Copyright 2020 DSuhoi
 * 
 * Пример TCP сервера (приём-передачи). 
 * (C++)
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <cstring>

// Значения результата выполнения программы
enum RESULT {
    NO_ERROR = 0,
    SOCKET,
    BIND,
    ACCEPT
};


inline RESULT initServer(int *listener, const int host)
{
    /*
     * AF_UNIX для передачи данных используется файловая система ввода/вывода Unix.
     * Константа AF_INET соответствует Internet-домену.
     * 
     * SOCK_STREAM. Передача потока данных с предварительной установкой соединения.     
     * SOCK_DGRAM. Передача данных в виде отдельных сообщений (датаграмм).
     * SOCK_RAW. Этот тип присваивается низкоуровневым (т. н. "сырым") сокетам.
     */
    
    *listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0) {
        perror("socket");
        return SOCKET;
    }
    
    /* 
     * Адресс IPv4
     * 
     * Вместо sockaddr можно использовать структуры sockaddr_XX (XX - суффикс, обозначающий домен: "un" - Unix, "in" - Internet и т. д.).
     * Поле sin_family соответствует полю sa_family в sockaddr.
     * В sin_port записывается номер порта.
     * В sin_addr - IP-адрес хоста.
     * 
     * Существует два порядка хранения байтов в слове и двойном слове. Один из них называется порядком хоста (host byte order),
     * другой - сетевым порядком (network byte order) хранения байтов. 
     * При указании IP-адреса и номера порта необходимо преобразовать число из порядка хоста в сетевой. 
     * Для этого используются функции htons (Host TO Network Short) и htonl (Host TO Network Long). 
     * Обратное преобразование выполняют функции ntohs и ntohl.
     * 
     * Если же вы готовы соединяться с клиентами через любой интерфейс, задайте в качестве адреса константу INADDR_ANY.
     */
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(host);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // Установка соединение
    if(bind(*listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return BIND;
    }
    
    // Создание запроса на соединение
    listen(*listener, 1);
    
    return NO_ERROR;
}


inline RESULT connection(int *listener)
{
    
    return NO_ERROR;
}


int main()
{
    RESULT result = NO_ERROR;
    const int host = 5555;
    // Дескриптор
    int listener;
    if((result = initServer(&listener, host)) != NO_ERROR)
        return result;
    
    if((result = connection(&listener)) != NO_ERROR)
        return result;
    
    // Конец TCP соединения
    close(listener);
    
    return result;
}
