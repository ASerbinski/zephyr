/*
 * Copyright (c) 2020 Stephanos Ioannidis <root@stephanos.io>
 * Copyright (C) 2010-2020 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <zephyr.h>
#include <stdlib.h>
#include <arm_math.h>
#include "../../common/test_common.h"

#include "unary_q31.pat"

#define SNR_ERROR_THRESH	((float32_t)100)
#define ABS_ERROR_THRESH_Q31	((q31_t)2)
#define ABS_ERROR_THRESH_Q63	((q63_t)(1 << 16))

#define NUM_MATRICES		(ARRAY_SIZE(in_dims) / 2)
#define MAX_MATRIX_DIM		(40)

#define OP2_ADD			(0)
#define OP2_SUB			(1)
#define OP1_SCALE		(0)
#define OP1_TRANS		(1)

static void test_op2(int op, const q31_t *ref, size_t length)
{
	size_t index;
	uint16_t *dims = (uint16_t *)in_dims;
	q31_t *tmp1, *tmp2, *output;
	uint16_t rows, columns;

	arm_matrix_instance_q31 mat_in1;
	arm_matrix_instance_q31 mat_in2;
	arm_matrix_instance_q31 mat_out;

	/* Allocate buffers */
	tmp1 = malloc(MAX_MATRIX_DIM * MAX_MATRIX_DIM * sizeof(q31_t));
	zassert_not_null(tmp1, ASSERT_MSG_BUFFER_ALLOC_FAILED);

	tmp2 = malloc(MAX_MATRIX_DIM * MAX_MATRIX_DIM * sizeof(q31_t));
	zassert_not_null(tmp2, ASSERT_MSG_BUFFER_ALLOC_FAILED);

	output = malloc(length * sizeof(q31_t));
	zassert_not_null(output, ASSERT_MSG_BUFFER_ALLOC_FAILED);

	/* Initialise contexts */
	mat_in1.pData = tmp1;
	mat_in2.pData = tmp2;
	mat_out.pData = output;

	/* Iterate matrices */
	for (index = 0; index < NUM_MATRICES; index++) {
		rows = *dims++;
		columns = *dims++;

		/* Initialise matrix dimensions */
		mat_in1.numRows = mat_in2.numRows = mat_out.numRows = rows;
		mat_in1.numCols = mat_in2.numCols = mat_out.numCols = columns;

		/* Load matrix data */
		memcpy(mat_in1.pData, in_com1, rows * columns * sizeof(q31_t));
		memcpy(mat_in2.pData, in_com2, rows * columns * sizeof(q31_t));

		/* Run test function */
		switch (op) {
		case OP2_ADD:
			arm_mat_add_q31(&mat_in1, &mat_in2, &mat_out);
			break;
		case OP2_SUB:
			arm_mat_sub_q31(&mat_in1, &mat_in2, &mat_out);
			break;
		default:
			zassert_unreachable("invalid operation");
		}

		/* Increment output pointer */
		mat_out.pData += (rows * columns);
	}

	/* Validate output */
	zassert_true(
		test_snr_error_q31(length, output, ref, SNR_ERROR_THRESH),
		ASSERT_MSG_SNR_LIMIT_EXCEED);

	zassert_true(
		test_near_equal_q31(length, output, ref, ABS_ERROR_THRESH_Q31),
		ASSERT_MSG_ABS_ERROR_LIMIT_EXCEED);

	/* Free buffers */
	free(tmp1);
	free(tmp2);
	free(output);
}

DEFINE_TEST_VARIANT3(op2, arm_mat_add_q31, OP2_ADD,
	ref_add, ARRAY_SIZE(ref_add));
DEFINE_TEST_VARIANT3(op2, arm_mat_sub_q31, OP2_SUB,
	ref_sub, ARRAY_SIZE(ref_sub));

static void test_op1(int op, const q31_t *ref, size_t length, bool transpose)
{
	size_t index;
	uint16_t *dims = (uint16_t *)in_dims;
	q31_t *tmp1, *output;
	uint16_t rows, columns;

	arm_matrix_instance_q31 mat_in1;
	arm_matrix_instance_q31 mat_out;

	/* Allocate buffers */
	tmp1 = malloc(MAX_MATRIX_DIM * MAX_MATRIX_DIM * sizeof(q31_t));
	zassert_not_null(tmp1, ASSERT_MSG_BUFFER_ALLOC_FAILED);

	output = malloc(length * sizeof(q31_t));
	zassert_not_null(output, ASSERT_MSG_BUFFER_ALLOC_FAILED);

	/* Initialise contexts */
	mat_in1.pData = tmp1;
	mat_out.pData = output;

	/* Iterate matrices */
	for (index = 0; index < NUM_MATRICES; index++) {
		rows = *dims++;
		columns = *dims++;

		/* Initialise matrix dimensions */
		mat_in1.numRows = rows;
		mat_in1.numCols = columns;
		mat_out.numRows = transpose ? columns : rows;
		mat_out.numCols = transpose ? rows : columns;

		/* Load matrix data */
		memcpy(mat_in1.pData, in_com1, rows * columns * sizeof(q31_t));

		/* Run test function */
		switch (op) {
		case OP1_SCALE:
			arm_mat_scale_q31(&mat_in1, 0x40000000, 0, &mat_out);
			break;
		case OP1_TRANS:
			arm_mat_trans_q31(&mat_in1, &mat_out);
			break;
		default:
			zassert_unreachable("invalid operation");
		}

		/* Increment output pointer */
		mat_out.pData += (rows * columns);
	}

	/* Validate output */
	zassert_true(
		test_snr_error_q31(length, output, ref, SNR_ERROR_THRESH),
		ASSERT_MSG_SNR_LIMIT_EXCEED);

	zassert_true(
		test_near_equal_q31(length, output, ref, ABS_ERROR_THRESH_Q31),
		ASSERT_MSG_ABS_ERROR_LIMIT_EXCEED);

	/* Free buffers */
	free(tmp1);
	free(output);
}

DEFINE_TEST_VARIANT4(op1, arm_mat_scale_q31, OP1_SCALE,
	ref_scale, ARRAY_SIZE(ref_scale), false);
DEFINE_TEST_VARIANT4(op1, arm_mat_trans_q31, OP1_TRANS,
	ref_trans, ARRAY_SIZE(ref_trans), true);

void test_matrix_unary_q31(void)
{
	ztest_test_suite(matrix_unary_q31,
		ztest_unit_test(test_op2_arm_mat_add_q31),
		ztest_unit_test(test_op2_arm_mat_sub_q31),
		ztest_unit_test(test_op1_arm_mat_scale_q31),
		ztest_unit_test(test_op1_arm_mat_trans_q31)
		);

	ztest_run_test_suite(matrix_unary_q31);
}
