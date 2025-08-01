/*
 * peripherals_setup.c
 *
 *  Created on: 7/16/2025
 *      Author: klysm
 */

#include "peripherals_setup.h"

void Setup_GPIO(void){
    EALLOW; //  Enables access to protected registers

    //GPIO34: output - RED LED
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;                 // PUD on
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;                 // Direction set as output
                                                        // only valid for GPIO
    GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = GPIO_MUX_CPU1;   // Chooses CPU1

    //GPIO31: output - BLUE LED
    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;                 // PUD on
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;                 // Direction set as output
                                                        // only valid for GPIO
    GpioCtrlRegs.GPACSEL4.bit.GPIO31 = GPIO_MUX_CPU1;   // Chooses CPU1

    // IO 0 - EPWM1A (J4 - 40)
    GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;
    // GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;               // only valid for GPIO 0 -> output
    GpioCtrlRegs.GPACSEL1.bit.GPIO0 = GPIO_MUX_CPU1;    // Chooses CPU1

    // IO 1 - EPWM1B (J4 - 39)
    GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;
    // GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;               // only valid for GPIO 1 -> output
    GpioCtrlRegs.GPACSEL1.bit.GPIO1 = GPIO_MUX_CPU1;    // Chooses CPU1

    // IO 2 - EPWM2A (J4 - 38)
    GpioCtrlRegs.GPAGMUX1.bit.GPIO2 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;
    // GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;               // only valid for GPIO 2 -> output
    GpioCtrlRegs.GPACSEL1.bit.GPIO2 = GPIO_MUX_CPU1;    // Chooses CPU1

    // IO 3 - EPWM2B (J4 - 37)
    GpioCtrlRegs.GPAGMUX1.bit.GPIO3 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;
    // GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;               // only valid for GPIO 3 -> output
    GpioCtrlRegs.GPACSEL1.bit.GPIO3 = GPIO_MUX_CPU1;    // Chooses CPU1

    // IO 4 - EPWM3A (J4 - 36)
    GpioCtrlRegs.GPAGMUX1.bit.GPIO4 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;
    // GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;               // only valid for GPIO 4 -> output
    GpioCtrlRegs.GPACSEL1.bit.GPIO4 = GPIO_MUX_CPU1;    // Chooses CPU1

    // IO 5 - EPWM3B (J4 - 35)
    GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;
    // GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;               // only valid for GPIO 5 -> output
    GpioCtrlRegs.GPACSEL1.bit.GPIO5 = GPIO_MUX_CPU1;    // Chooses CPU1

    // PWM 7A DAC3 - EPWM3A (J8 - 72)
    GpioCtrlRegs.GPEGMUX2.bit.GPIO157 = 0;
    GpioCtrlRegs.GPEMUX2.bit.GPIO157 = 1;
    GpioCtrlRegs.GPEPUD.bit.GPIO157 = 1;

    // PWM 8A DAC1 - EPWM3B (J4 - 32)
    GpioCtrlRegs.GPEGMUX2.bit.GPIO159 = 0;
    GpioCtrlRegs.GPEMUX2.bit.GPIO159 = 1;
    GpioCtrlRegs.GPEPUD.bit.GPIO159 = 1;

    EDIS; //  Disables access to protected registers
}

void Setup_DAC(void){
    EALLOW; //  Enables access to protected registers

    // Configure DAC-A and DAC-B control registers
    DacaRegs.DACCTL.all = 0x0001;
    DacbRegs.DACCTL.all = 0x0001;

    // Set DAC-A and DAC-B output to mid-range
    DacaRegs.DACVALS.all = 0x0800;
    DacbRegs.DACVALS.all = 0x0800;

    // Enable DAC-A and DAC-B output
    DacaRegs.DACOUTEN.bit.DACOUTEN = 1;                 // 0 = disable, 1 = enable
    DacbRegs.DACOUTEN.bit.DACOUTEN = 1;                 // 0 = disable, 1 = enable

    // DAC-A and DAC-B lock control register
    DacaRegs.DACLOCK.all = 0x0000;
    DacbRegs.DACLOCK.all = 0x0000;

    EDIS; //  Disables access to protected registers
}


void Setup_ePWM1(void){                              // Enhanced Pulse Width Modulation 1
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;                // Enable module clock

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;            // Disable counter clock

    EPwm1Regs.TBPRD = 50000;                         // Period F_osc/2*F_pwm or F_osc/4*F_pwm
    EPwm1Regs.TBPHS.bit.TBPHS = 0;                   // Phase is 0
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.TBCTR = 0;                             // Clear counter
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Count up/down
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;          // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;         // Pre-scale
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    //EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD >> 1;  // Duty 50% (Pulse width)
    EPwm1Regs.CMPA.bit.CMPA = 12500;                 // 25%


    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;      // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;      // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set actions for EPwm1A, AQ_SET and AQ_CLEAR goes to 75%
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;

    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;        // Active High complementary in the Polarity Selection
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;   // Enable Dead-band
    EPwm1Regs.DBFED.bit.DBFED = 44;                  // Time = DBxED * 2 * TBCLK
    EPwm1Regs.DBRED.bit.DBRED = 9;                   // Rising edge delay time

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;            // Enable counter clock
    EDIS;
}

void Setup_ePWM2(void){                              // Enhanced Pulse Width Modulation 2
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;                // Enable module clock

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;            // Disable counter clock

    EPwm2Regs.TBPRD = 50000;                         // Period F_osc/2*F_pwm or F_osc/4*F_pwm
    EPwm2Regs.TBPHS.bit.TBPHS = 0;                   // Phase is 0
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm2Regs.TBCTR = 0;                             // Clear counter
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Count up/down
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;          // Disable phase loading
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;         // Pre-scale
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm2Regs.CMPA.bit.CMPA = EPwm2Regs.TBPRD >> 1;  // Duty 50% (Pulse width)

    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;      // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;      // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Set actions for EPwm1A
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;

    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;        // Active High complementary in the Polarity Selection
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;   // Enable Dead-band
    EPwm1Regs.DBFED.bit.DBFED = 44;                  // Time = DBxED * 2 * TBCLK
    EPwm1Regs.DBRED.bit.DBRED = 9;                   // Rising edge delay time

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;            // Enable counter clock
    EDIS;
}

void Setup_ePWM3(void){                              // Enhanced Pulse Width Modulation 3
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM3 = 1;                // Enable module clock

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;            // Disable counter clock

    EPwm3Regs.TBPRD = 50000;                         // Period F_osc/2*F_pwm or F_osc/4*F_pwm
    EPwm3Regs.TBPHS.bit.TBPHS = 0;                   // Phase is 0
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm3Regs.TBCTR = 0;                             // Clear counter
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Count up/down
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;          // Disable phase loading
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;         // Pre-scale
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    //EPwm3Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD >> 1;  // Duty 50% (Pulse width)
    EPwm3Regs.CMPA.bit.CMPA = 12500;

    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;      // Load registers every ZERO
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;      // Load registers every ZERO
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Set actions for EPwm3A, AQ_CLEAR and AQ_SET goes to 25%
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;

    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;        // Active High complementary in the Polarity Selection
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;   // Enable Dead-band
    EPwm3Regs.DBFED.bit.DBFED = 44;                  // Time = DBxED * 2 * TBCLK
    EPwm3Regs.DBRED.bit.DBRED = 9;                   // Rising edge delay time

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;            // Enable counter clock
    EDIS;
}

void Setup_ePWM7(void){
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM7 = 1;               // Enable clock

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    EPwm7Regs.TBPRD = 5000;                         // Period (up/down) 10Khz Clock/4/fpwm LAB PWM
    EPwm7Regs.CMPA.bit.CMPA = 0;                    // 50% pulse width
    EPwm7Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up/down

    EPwm7Regs.TBPHS.bit.TBPHS = 0;                  // Set phase register to 0
    EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;    // Sync down-stream module
    EPwm7Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Master module
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
    EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm7Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;

    EPwm7Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm7Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // set actions for EPWM10A
    EPwm7Regs.AQCTLA.bit.CAD = AQ_SET;

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;            // Enable counter clock
    EDIS;
}

void Setup_ePWM8(void){
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM8 = 1;               // Enable clock

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    EPwm8Regs.TBPRD = 5000;                         // Period (up/down) Clock/4/fpwm LAB PWM
    EPwm8Regs.CMPA.bit.CMPA = 0;                    // 50% pulse width
    EPwm8Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up/down

    EPwm8Regs.TBPHS.bit.TBPHS = 0;                  // Set phase register to 0
    EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // Sync down-stream module
    EPwm8Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Master module
    EPwm8Regs.TBCTL.bit.PHSDIR = TB_DOWN;          // Master module
    EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
    EPwm8Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm8Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;

    EPwm8Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm8Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // set actions for EPWM10A
    EPwm8Regs.AQCTLA.bit.CAD = AQ_SET;

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;            // Enable counter clock
    EDIS;
}

void Setup_ePWM10(void){
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM10 = 1;               // Enable clock

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    EPwm10Regs.TBPRD = 5000;                         // Period (up/down) 10Khz Clock/4/fpwm LAB PWM

    EPwm10Regs.CMPA.bit.CMPA = EPwm10Regs.TBPRD >> 1;// 50% pulse width

    EPwm10Regs.TBPHS.bit.TBPHS = 0;                  // Phase is 0
    EPwm10Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    EPwm10Regs.TBCTR = 0x0000;                       // Clear counter

    EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up/down
    EPwm10Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Disable phase loading

    EPwm10Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
    EPwm10Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm10Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm10Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm10Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    EPwm10Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm10Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm10Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // set actions for EPWM10A
    EPwm10Regs.AQCTLA.bit.CAD = AQ_SET;

    //Trigger ADC
    EPwm10Regs.ETSEL.bit.SOCAEN = 1;                 // Enable SOC on A group
    EPwm10Regs.ETSEL.bit.SOCASEL = ET_CTR_PRDZERO;   // Dispara ADC no topo
    EPwm10Regs.ETPS.bit.SOCAPRD = ET_1ST;            // Trigger on every event

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;            // Enable counter clock
    EDIS;
}

void Setup_ADC(void){
    Uint16 acqps;

    // determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
        acqps = 14;                         // 75ns
    else                                    // resolution is 16-bit
        acqps = 63;                         // 320ns

    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;

    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;   // Set pulse one cycle before the result
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;      // Power up the ADC
    DELAY_US(1000);                         // Delay for 1ms to allow ADC timer to power up

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 3;      // ADCINA3 - J3-26
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x17;

    // SOC = Start of conversion
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 4;      // ADCINA3 - J7-69
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;  // sample window is 15 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x17;

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0x01;   // end of SOC1 will set INT1 flag (source)
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;        // enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      // make sure INT1 flag is cleared



}
