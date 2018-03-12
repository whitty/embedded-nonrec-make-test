void exit(int status)
{
    (void)status;
    for (;;)
        continue;
}

void _exit(int status)
{
    (void)status;
    for (;;)
        continue;
}

void atexit(void (*function)(void))
{
    (void)function;
    // assert();
}
