/*
 * tcp_client.c
 * 
 * Copyright 2020 DSuhoi
 * 
 * Пример TCP (UDP) клиента (приём-передачи). 
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


inline RESULT init_client(int* sock, const int host)
{
    /*
     * AF_UNIX для передачи данных используется файловая система ввода/вывода Unix.
     * Константа AF_INET соответствует Internet-домену.
     * 
     * SOCK_STREAM. Передача потока данных с предварительной установкой соединения.     
     * SOCK_DGRAM. Передача данных в виде отдельных сообщений (датаграмм).
     * SOCK_RAW. Этот тип присваивается низкоуровневым (т. н. "сырым") сокетам.
     */
    
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if (*sock < 0) {
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
    
    // Установка соединения с сервером
    if (connect(*sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return BIND;
    }
    
    // Сообщение о подключении
    const char mess[] = "connect!\n";
    send(*sock, mess, sizeof(mess), 0);
    
    /*
     * Функции для UDP протокола
     * sendto(*sock, mess, sizeof(mess), 0, (struct sockaddr *)&addr, sizeof(addr));
     * recvto(*sock, mess, sizeof(mess), 0, (struct sockaddr *)&addr, sizeof(addr));
     */
    
    return NO_ERROR;
}


inline RESULT connection(int* sock)
{
    // Параметры буфера ввода/вывода
    const size_t BUF_LEN = 1024;
    char buf[BUF_LEN] = {0};
    const char STOP_CHR = '#';
    
    do {
        // Ожидание ответа от сервера
        while(recv(*sock, buf, BUF_LEN, 0) <= 0);
        printf(">>%s", buf);
        // Если получен символ окончания передачи, то разрываем соединение
        if (buf[0] == '#')
            break;
        
        printf("<<");
        // Очистка буфера
        memset(buf, 0, BUF_LEN);
        // Чтение строки из потока
        fgets(buf, BUF_LEN, stdin);
        // Передача строки
        send(*sock, buf, BUF_LEN, 0);
    } while(buf[0] != STOP_CHR);
    
    return NO_ERROR;
}


int main(int argc, char** argv)
{
    RESULT result;
    // Номер порта
    const int host = 5558;
    // Дескриптор
    int sock;
    if ((result = init_client(&sock, host)) != NO_ERROR)
        return result;
        
    if ((result = connection(&sock)) != NO_ERROR)
        return result;
    
    // Конец TCP соединения    
    close(sock);

    return 0;
}
