/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * All rights reserved.
 *
 * Copyright (c) 2015 Xilinx, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the <ORGANIZATION> nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "xscugic.h"
#include "platform_info.h"

#define INTC_DEVICE_ID		XPAR_SCUGIC_0_DEVICE_ID

extern void bm_env_isr(int vector);
extern XScuGic xInterruptController;

/* Complete Interrupt Controller setup, FreeRTOS is doing pre-init */
static int app_gic_initialize(void)
{
	/* Connect Interrupt ID with ISR */
	XScuGic_Connect(&xInterruptController, VRING1_IPI_INTR_VECT,
			   (Xil_ExceptionHandler)bm_env_isr,
			   (void *)VRING1_IPI_INTR_VECT);

	XScuGic_Connect(&xInterruptController, VRING0_IPI_INTR_VECT,
				   (Xil_ExceptionHandler)bm_env_isr,
				   (void *)VRING0_IPI_INTR_VECT);

	return 0;
}

/* initialization entry point called from main()*/
/* return 0 on success */
int init_system(void)
{

	/* configure the global interrupt controller */
	app_gic_initialize();

    return 0;
}
