#ifndef _THREAD_H_
#define _THREAD_H_
#include <thread>
#include <utility>

/** Encapsula los metodos para iniciar, correr y joinear hilos.
 *
 */
class Thread {
private:
    std::thread thread;

public:
    Thread() {
    }

    void start() {
        thread = std::thread(&Thread::run, this);
    }

    void join() {
        thread.join();
    }

    virtual void run() = 0;
    virtual ~Thread() {
    }

private:
    // deshabilito el constructor por copia
    Thread(const Thread&) = delete;
    // deshabilito el operador de asignacion para evitar que se
    // copie el objeto.
    Thread& operator=(const Thread&) = delete;

    // constructor por movimiento.
    //
    Thread(Thread&& other) {
        this->thread = std::move(other.thread);
    }

    Thread& operator=(Thread&& other) {
        this->thread = std::move(other.thread);
        return *this;
    }
};

#endif /* _THREAD_H_ */
