//
// Created by XingfengYang on 2020/6/16.
//

#ifndef __KERNEL_VMM_H__
#define __KERNEL_VMM_H__

void vmm_init();

void vmm_enable();

extern int __PAGE_TABLE;

#endif //__KERNEL_VMM_H__
