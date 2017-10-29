static int lock = 0;
void spin_lock() {
    while (lock);
    lock = 1;
}

void spin_unlock() {
    lock = 0;
}