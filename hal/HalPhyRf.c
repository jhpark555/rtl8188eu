/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

 #include "odm_precomp.h"

/* 3============================================================ */
/* 3 IQ Calibration */
/* 3============================================================ */

void ODM_ResetIQKResult(struct odm_dm_struct *pDM_Odm)
{
	u1Byte		i;
	struct adapter *adapt = pDM_Odm->Adapter;

	if (!IS_HARDWARE_TYPE_8192D(adapt))
		return;
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,
		     ("PHY_ResetIQKResult:: settings regs %d default regs %d\n",
		     (u32)(sizeof(pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting) /
		     sizeof(struct ijk_matrix_regs_set)), IQK_Matrix_Settings_NUM));
	/* 0xe94, 0xe9c, 0xea4, 0xeac, 0xeb4, 0xebc, 0xec4, 0xecc */

	for (i = 0; i < IQK_Matrix_Settings_NUM; i++) {
		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[i].Value[0][0] = 0x100;
		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[i].Value[0][2] = 0x100;
		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[i].Value[0][4] = 0x100;
		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[i].Value[0][6] = 0x100;

		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[i].Value[0][1] = 0;
		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[i].Value[0][3] = 0;
		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[i].Value[0][5] = 0;
		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[i].Value[0][7] = 0;

		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[i].bIQKDone = false;
	}
}

u1Byte ODM_GetRightChnlPlaceforIQK(u1Byte chnl)
{
	u1Byte	channel_all[ODM_TARGET_CHNL_NUM_2G_5G] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64,
		100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122,
		124, 126, 128, 130, 132, 134, 136, 138, 140, 149, 151, 153,
		155, 157, 159, 161, 163, 165
	};
	u1Byte	place = chnl;

	if (chnl > 14) {
		for (place = 14; place < sizeof(channel_all); place++) {
			if (channel_all[place] == chnl)
				return place-13;
		}
	}
	return 0;
}
