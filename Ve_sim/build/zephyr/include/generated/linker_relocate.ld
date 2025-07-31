

/* Linker section for memory region ITCM for  TEXT section  */

	SECTION_PROLOGUE(.itcm_text_reloc,,)
        {
                . = ALIGN(4);
                
                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.device_is_ready))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_enable_octal_mode))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_erase))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_erase_chip))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_erase_sector))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_get_vendor_id))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_init))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_page_program))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_read))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_read_status))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_wait_bus_busy))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_write))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_write_enable))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.flash_flexspi_nor_write_status))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.rel.text.z_log_msg_runtime_create))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.device_is_ready))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_enable_octal_mode))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_erase))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_erase_chip))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_erase_sector))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_get_parameters))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_get_vendor_id))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_init))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_page_program))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_pages_layout))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_read))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_read_status))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_wait_bus_busy))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_write))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_write_enable))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.flash_flexspi_nor_write_status))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.k_is_user_context))

                KEEP(*flash_mcux_flexspi_is25lx064.c.obj(.text.z_log_msg_runtime_create))

                KEEP(*flexspi.c.obj(.rel.text.CLOCK_DisableClock))

                KEEP(*flexspi.c.obj(.rel.text.CLOCK_EnableClock))

                KEEP(*flexspi.c.obj(.rel.text.CLOCK_GetRootClockSource))

                KEEP(*flexspi.c.obj(.rel.text.CLOCK_SetRootClockDiv))

                KEEP(*flexspi.c.obj(.rel.text.flexspi_clock_set_freq))

                KEEP(*flexspi.c.obj(.text.CLOCK_ControlGate))

                KEEP(*flexspi.c.obj(.text.CLOCK_DisableClock))

                KEEP(*flexspi.c.obj(.text.CLOCK_EnableClock))

                KEEP(*flexspi.c.obj(.text.CLOCK_GetRootClockMux))

                KEEP(*flexspi.c.obj(.text.CLOCK_GetRootClockSource))

                KEEP(*flexspi.c.obj(.text.CLOCK_SetRootClockDiv))

                KEEP(*flexspi.c.obj(.text.FLEXSPI_Enable))

                KEEP(*flexspi.c.obj(.text.FLEXSPI_GetBusIdleStatus))

                KEEP(*flexspi.c.obj(.text.FLEXSPI_SoftwareReset))

                KEEP(*flexspi.c.obj(.text.flexspi_clock_set_freq))

                KEEP(*fsl_flexspi.c.obj(.rel.text.CLOCK_EnableClock))

                KEEP(*fsl_flexspi.c.obj(.rel.text.EnableIRQ))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI1_DriverIRQHandler))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI2_DriverIRQHandler))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_CalculateDll))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_CheckAndClearError))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_Deinit))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_GetDefaultConfig))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_GetInstance))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_Init))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_Memset))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_ReadBlocking))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_SetFlashConfig))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_TransferAbort))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_TransferBlocking))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_TransferCreateHandle))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_TransferGetCount))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_TransferHandleIRQ))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_TransferNonBlocking))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_UpdateDllValue))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_UpdateLUT))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_UpdateRxSampleClock))

                KEEP(*fsl_flexspi.c.obj(.rel.text.FLEXSPI_WriteBlocking))

                KEEP(*fsl_flexspi.c.obj(.text.CLOCK_ControlGate))

                KEEP(*fsl_flexspi.c.obj(.text.CLOCK_EnableClock))

                KEEP(*fsl_flexspi.c.obj(.text.EnableIRQ))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI1_DriverIRQHandler))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI2_DriverIRQHandler))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_CalculateDll))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_CheckAndClearError))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_ClearInterruptStatusFlags))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_Deinit))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_DisableInterrupts))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_EnableInterrupts))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_GetBusIdleStatus))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_GetDefaultConfig))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_GetInstance))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_Init))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_Memset))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_ReadBlocking))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_SetFlashConfig))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_SoftwareReset))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_TransferAbort))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_TransferBlocking))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_TransferCreateHandle))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_TransferGetCount))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_TransferHandleIRQ))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_TransferNonBlocking))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_UpdateDllValue))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_UpdateLUT))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_UpdateRxSampleClock))

                KEEP(*fsl_flexspi.c.obj(.text.FLEXSPI_WriteBlocking))

                KEEP(*fsl_flexspi.c.obj(.text.__NVIC_EnableIRQ))

                KEEP(*memc_mcux_flexspi.c.obj(.rel.text.memc_flexspi_get_ahb_address))

                KEEP(*memc_mcux_flexspi.c.obj(.rel.text.memc_flexspi_init))

                KEEP(*memc_mcux_flexspi.c.obj(.rel.text.memc_flexspi_reset))

                KEEP(*memc_mcux_flexspi.c.obj(.rel.text.memc_flexspi_set_device_config))

                KEEP(*memc_mcux_flexspi.c.obj(.rel.text.memc_flexspi_transfer))

                KEEP(*memc_mcux_flexspi.c.obj(.rel.text.memc_flexspi_update_clock))

                KEEP(*memc_mcux_flexspi.c.obj(.rel.text.memc_flexspi_wait_bus_idle))

                KEEP(*memc_mcux_flexspi.c.obj(.rel.text.pinctrl_apply_state))

                KEEP(*memc_mcux_flexspi.c.obj(.rel.text.pinctrl_apply_state_direct))

                KEEP(*memc_mcux_flexspi.c.obj(.rel.text.z_log_msg_runtime_create))

                KEEP(*memc_mcux_flexspi.c.obj(.text.FLEXSPI_GetBusIdleStatus))

                KEEP(*memc_mcux_flexspi.c.obj(.text.FLEXSPI_SoftwareReset))

                KEEP(*memc_mcux_flexspi.c.obj(.text.clock_control_get_rate))

                KEEP(*memc_mcux_flexspi.c.obj(.text.clock_control_set_rate))

                KEEP(*memc_mcux_flexspi.c.obj(.text.k_is_user_context))

                KEEP(*memc_mcux_flexspi.c.obj(.text.memc_flexspi_get_ahb_address))

                KEEP(*memc_mcux_flexspi.c.obj(.text.memc_flexspi_init))

                KEEP(*memc_mcux_flexspi.c.obj(.text.memc_flexspi_is_running_xip))

                KEEP(*memc_mcux_flexspi.c.obj(.text.memc_flexspi_reset))

                KEEP(*memc_mcux_flexspi.c.obj(.text.memc_flexspi_set_device_config))

                KEEP(*memc_mcux_flexspi.c.obj(.text.memc_flexspi_transfer))

                KEEP(*memc_mcux_flexspi.c.obj(.text.memc_flexspi_update_clock))

                KEEP(*memc_mcux_flexspi.c.obj(.text.memc_flexspi_wait_bus_idle))

                KEEP(*memc_mcux_flexspi.c.obj(.text.pinctrl_apply_state))

                KEEP(*memc_mcux_flexspi.c.obj(.text.pinctrl_apply_state_direct))

                KEEP(*memc_mcux_flexspi.c.obj(.text.z_log_msg_runtime_create))

                . = ALIGN(4);
	} 
#ifdef CONFIG_XIP
GROUP_DATA_LINK_IN(ITCM , ROMABLE_REGION)
#else
GROUP_DATA_LINK_IN(ITCM , ITCM )
#endif

        __itcm_text_reloc_end = .;
        __itcm_text_reloc_start = ADDR(.itcm_text_reloc);
        __itcm_text_reloc_size = __itcm_text_reloc_end - __itcm_text_reloc_start;

        __itcm_text_rom_start = LOADADDR(.itcm_text_reloc);
