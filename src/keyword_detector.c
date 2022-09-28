/*
 * Copyright (c) 2019 SK Telecom Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "libWakeupApi.h"
#include "keyword_detector.h"

static WakeupHandle wakeup_handle = NULL;

int kwd_initialize(const char *model_net_file, const char *model_search_file)
{
	if (!model_net_file) {
		fprintf(stderr, "model_net_file is empty\n");
		return -1;
	} else {
		struct stat stat_buf;

		if (stat(model_net_file, &stat_buf) < 0) {
			fprintf(stderr, "errno[%d]: %s (%s)\n", errno,
				strerror(errno), model_net_file);
			return -1;
		}
	}

	if (!model_search_file) {
		fprintf(stderr, "model_search_file is empty\n");
		return -1;
	} else {
		struct stat stat_buf;

		if (stat(model_search_file, &stat_buf) < 0) {
			fprintf(stderr, "errno[%d]: %s (%s)\n", errno,
				strerror(errno), model_search_file);
			return -1;
		}
	}

	if (wakeup_handle)
		return 0;

	wakeup_handle = Wakeup_Create(model_net_file, model_search_file, 0);

	return (wakeup_handle == NULL) ? -1 : 0;
}

int kwd_put_audio(short *buf, int buf_size)
{
	if (wakeup_handle == NULL) {
		fprintf(stderr, "wd is not initialized");
		return -1;
	}

	return Wakeup_PutAudio(wakeup_handle, buf, (buf_size / 2));
}

void kwd_deinitialize()
{
	if (wakeup_handle == NULL) {
		return;
	}

	Wakeup_Destroy(wakeup_handle);
	wakeup_handle = NULL;
}

int kwd_get_start_time()
{
	if (wakeup_handle == NULL) {
		fprintf(stderr, "wd is not initialized");
		return -1;
	}

	return Wakeup_GetStartTime(wakeup_handle);
}

int kwd_get_end_time()
{
	if (wakeup_handle == NULL) {
		fprintf(stderr, "wd is not initialized");
		return -1;
	}

	return Wakeup_GetEndTime(wakeup_handle);
}

int kwd_get_detection_time()
{
	if (wakeup_handle == NULL) {
		fprintf(stderr, "wd is not initialized");
		return -1;
	}

	return Wakeup_GetDetectionTime(wakeup_handle);
}

int kwd_get_start_margin()
{
	if (wakeup_handle == NULL) {
		fprintf(stderr, "wd is not initialized");
		return -1;
	}

	return Wakeup_GetStartMargin(wakeup_handle);
}

float kwd_get_power()
{
	if (wakeup_handle == NULL) {
		fprintf(stderr, "wd is not initialized");
		return -1;
	}

	return Wakeup_GetPower(wakeup_handle);
}

float kwd_get_score()
{
	if (wakeup_handle == NULL) {
		fprintf(stderr, "wd is not initialized");
		return -1;
	}

	return Wakeup_GetScore(wakeup_handle);
}