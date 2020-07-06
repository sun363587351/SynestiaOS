//
// Created by XingfengYang on 2020/6/26.
//

#include <thread.h>
#include <kstack.h>
#include <kheap.h>
#include <stdlib.h>

Thread *initThread;

void thread_insert_to_rb_tree(RBNode *root, RBNode *node) {
    uint32_t parentValue = getNode(root, Thread, rbTree)->runtimVirtualNs;
    uint32_t nodeValue = getNode(node, Thread, rbTree)->runtimVirtualNs;
    if (nodeValue >= parentValue) {
        if (root->right != nullptr) {
            thread_insert_to_rb_tree(root->right, node);
        } else {
            root->right = node;
            rbtree_balance(root, node);
        }
    } else {
        if (root->left != nullptr) {
            thread_insert_to_rb_tree(root->left, node);
        } else {
            root->left = node;
            rbtree_balance(root, node);
        }
    }
}

Thread *thread_create(const char *name, ThreadStartRoutine entry, void *arg, uint32_t priority) {
    KernelStack *kernelStack = nullptr;
    // 1. allocate stack memory from kernel heap for idle task
    KernelStatus kernelStackAllocateState = kstack_allocate(kernelStack);
    if (kernelStack != nullptr && kernelStackAllocateState != ERROR) {
        // 1. init kernel stack
        kstack_push(kernelStack, 0x14141414);   // R14
        kstack_push(kernelStack, kernelStack->virtualMemoryAddress);   // R13
        kstack_push(kernelStack, 0x12121212);   // R12
        kstack_push(kernelStack, 0x11111111);   // R11
        kstack_push(kernelStack, 0x10101010);   // R10
        kstack_push(kernelStack, 0x09090909);   // R09
        kstack_push(kernelStack, 0x08080808);   // R08
        kstack_push(kernelStack, 0x07070707);   // R07
        kstack_push(kernelStack, 0x06060606);   // R06
        kstack_push(kernelStack, 0x05050505);   // R05
        kstack_push(kernelStack, 0x04040404);   // R04
        kstack_push(kernelStack, 0x03030303);   // R03
        kstack_push(kernelStack, 0x02020202);   // R02
        kstack_push(kernelStack, 0x01010101);   // R01

        Thread *thread = (Thread *) kheap_alloc(sizeof(Thread));
        thread->magic = THREAD_MAGIC;
        thread->threadStatus = THREAD_INITIAL;
        thread->stack = kernelStack;
        thread->priority = priority;
        thread->currCpu = INVALID_CPU;
        thread->lastCpu = INVALID_CPU;
        thread->entry = (ThreadStartRoutine) entry;
        thread->runtimeNs = 0;
        thread->runtimVirtualNs = 0;
        thread->pid = 0;
        strcpy(thread->name, name);
        thread->arg = arg;
        // todo : other properties, like list

        thread_insert_to_rb_tree(initThread->rbTree, thread->rbTree);
        return thread;
    }
    return nullptr;
}

uint32_t *idle_thread_routine(void *arg) {
    asm volatile("wfi");
}

Thread *thread_create_idle_thread(uint32_t cpuNum) {
    KernelStack *kernelStack = nullptr;
    // 1. allocate stack memory from kernel heap for idle task
    KernelStatus kernelStackAllocateState = kstack_allocate(kernelStack);
    if (kernelStack != nullptr && kernelStackAllocateState != ERROR) {
        // 1. init kernel stack
        kstack_push(kernelStack, 0x14141414);   // R14
        kstack_push(kernelStack, kernelStack->virtualMemoryAddress);   // R13
        kstack_push(kernelStack, 0x12121212);   // R12
        kstack_push(kernelStack, 0x11111111);   // R11
        kstack_push(kernelStack, 0x10101010);   // R10
        kstack_push(kernelStack, 0x09090909);   // R09
        kstack_push(kernelStack, 0x08080808);   // R08
        kstack_push(kernelStack, 0x07070707);   // R07
        kstack_push(kernelStack, 0x06060606);   // R06
        kstack_push(kernelStack, 0x05050505);   // R05
        kstack_push(kernelStack, 0x04040404);   // R04
        kstack_push(kernelStack, 0x03030303);   // R03
        kstack_push(kernelStack, 0x02020202);   // R02
        kstack_push(kernelStack, 0x01010101);   // R01

        // 2. idle thread
        Thread *idleThread = (Thread *) kheap_alloc(sizeof(Thread));
        idleThread->magic = THREAD_MAGIC;
        idleThread->threadStatus = THREAD_READY;
        idleThread->stack = kernelStack;
        idleThread->priority = IDLE_PRIORITY;
        idleThread->currCpu = INVALID_CPU;
        idleThread->lastCpu = INVALID_CPU;
        idleThread->runtimeNs = 0;
        idleThread->runtimVirtualNs = 0;
        idleThread->entry = (ThreadStartRoutine) idle_thread_routine;
        idleThread->pid = 0;
        strcpy(idleThread->name, "idle");

        // todo : other properties, like list
        return idleThread;
    }
    return nullptr;
}

KernelStatus thread_reschedule(void) {
    // todo
    return OK;
}

KernelStatus thread_sleep(uint32_t deadline) {
    // todo
    return OK;
}

KernelStatus thread_detach(Thread *thread) {
    // todo
    return OK;
}

KernelStatus thread_join(Thread *thread, int *retcode, uint32_t deadline) {
    // todo
    return OK;
}

KernelStatus init_thread_struct(Thread *thread, const char *name) {
    KernelStack *kernelStack = nullptr;
    // 1. allocate stack memory from kernel heap for idle task
    KernelStatus kernelStackAllocateState = kstack_allocate(kernelStack);
    if (kernelStack != nullptr && kernelStackAllocateState != ERROR) {
        // 1. init kernel stack
        kstack_push(kernelStack, 0x14141414);   // R14
        kstack_push(kernelStack, kernelStack->virtualMemoryAddress);   // R13
        kstack_push(kernelStack, 0x12121212);   // R12
        kstack_push(kernelStack, 0x11111111);   // R11
        kstack_push(kernelStack, 0x10101010);   // R10
        kstack_push(kernelStack, 0x09090909);   // R09
        kstack_push(kernelStack, 0x08080808);   // R08
        kstack_push(kernelStack, 0x07070707);   // R07
        kstack_push(kernelStack, 0x06060606);   // R06
        kstack_push(kernelStack, 0x05050505);   // R05
        kstack_push(kernelStack, 0x04040404);   // R04
        kstack_push(kernelStack, 0x03030303);   // R03
        kstack_push(kernelStack, 0x02020202);   // R02
        kstack_push(kernelStack, 0x01010101);   // R01

        thread->magic = THREAD_MAGIC;
        thread->threadStatus = THREAD_INITIAL;
        thread->stack = kernelStack;
        thread->priority = IDLE_PRIORITY;
        thread->currCpu = INVALID_CPU;
        thread->runtimeNs = 0;
        thread->runtimVirtualNs = 0;
        thread->lastCpu = INVALID_CPU;
        thread->entry = (ThreadStartRoutine) idle_thread_routine;
        thread->pid = 0;
        strcpy(thread->name, name);
        return OK;
    }
    return ERROR;
}

KernelStatus thread_exit(uint32_t returnCode) {
    // todo
    return OK;
}

KernelStatus thread_kill(Thread *thread) {
    // todo
    return OK;
}
