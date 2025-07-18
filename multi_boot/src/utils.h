#ifndef UTILS_H_
#define UTILS_H_
#ifdef BOOTLOADER
int utils_open(void);
int utils_write(void *buf,int size);
int utils_read(const void *buf,int size);
void utils_close(void);
__attribute__((section(".utils"),used))
static void *utils_interface[4]{
    (void *)(utils_open),
    (void *)(utils_write),
    (void *)(utils_read),
    (void *)(utils_close)
};
#else
static void **utils_interface = (void **)(0x00000400);
static inline int utils_open(void){
    int(*do_open)(void) = (int(*)(void))(utils_interface);
    return do_open();
}
static inline int utils_write(void* buf,int size){
    int(*do_write)(void*,int) = (int(*)(void*,int))(utils_interface[1]);
    return do_write(buf,size);
}
static inline int utils_read(const void *buf,int size){
    int(*do_read)(const void*,int) = (int(*)(const void*,int))(utils_interface[2]);
    return do_read(buf,size);
}
static inline void utils_close(void){
    void(*do_close)(void) = (void(*)(void))(utils_interface[3]);
    do_close();
}
#endif
#endif
