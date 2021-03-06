/**
 * Copyright 2021 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MICRO_LITE_MICRO_CODER_GENERATOR_CONST_BLOCKS_BENCH_LOAD_INPUT_H_
#define MICRO_LITE_MICRO_CODER_GENERATOR_CONST_BLOCKS_BENCH_LOAD_INPUT_H_
static const char load_input_h[] =
  "/**\n"
  " * Copyright 2021 Huawei Technologies Co., Ltd\n"
  " *\n"
  " * Licensed under the Apache License, Version 2.0 (the \"License\");\n"
  " * you may not use this file except in compliance with the License.\n"
  " * You may obtain a copy of the License at\n"
  " *\n"
  " * http://www.apache.org/licenses/LICENSE-2.0\n"
  " *\n"
  " * Unless required by applicable law or agreed to in writing, software\n"
  " * distributed under the License is distributed on an \"AS IS\" BASIS,\n"
  " * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n"
  " * See the License for the specific language governing permissions and\n"
  " * limitations under the License.\n"
  " */\n"
  "\n"
  "#ifndef MICRO_EXAMPLE_LOAD_INPUT_LOAD_INPUT_H_\n"
  "#define MICRO_EXAMPLE_LOAD_INPUT_LOAD_INPUT_H_\n"
  "void *ReadInputData(const char *real_input_path, int *size);\n"
  "\n"
  "void SaveOutputData(char *final_name, unsigned char *output_data, unsigned int out_size);\n"
  "\n"
  "int ReadInputsFile(char *path, void **buffers, const int *inputs_size, int inputs_num);\n"
  "\n"
  "#endif  // MICRO_EXAMPLE_LOAD_INPUT_LOAD_INPUT_H_\n";

static const char load_input_c[] =
  "/**\n"
  " * Copyright 2021 Huawei Technologies Co., Ltd\n"
  " *\n"
  " * Licensed under the Apache License, Version 2.0 (the \"License\");\n"
  " * you may not use this file except in compliance with the License.\n"
  " * You may obtain a copy of the License at\n"
  " *\n"
  " * http://www.apache.org/licenses/LICENSE-2.0\n"
  " *\n"
  " * Unless required by applicable law or agreed to in writing, software\n"
  " * distributed under the License is distributed on an \"AS IS\" BASIS,\n"
  " * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n"
  " * See the License for the specific language governing permissions and\n"
  " * limitations under the License.\n"
  " */\n"
  "\n"
  "#include \"load_input.h\"\n"
  "#include <stdlib.h>\n"
  "#include <stdio.h>\n"
  "#include <string.h>\n"
  "\n"
  "void *ReadInputData(const char *real_input_path, int *size) {\n"
  "  if (real_input_path == NULL) {\n"
  "    return NULL;\n"
  "  }\n"
  "  if (strstr(real_input_path, \".bin\") || strstr(real_input_path, \".net\")) {\n"
  "    FILE *file;\n"
  "    file = fopen(real_input_path, \"rb+\");\n"
  "    if (!file) {\n"
  "      printf(\"Can't find %s\\n\", real_input_path);\n"
  "      return NULL;\n"
  "    }\n"
  "    int curr_file_posi = ftell(file);\n"
  "    fseek(file, 0, SEEK_END);\n"
  "    *size = ftell(file);\n"
  "    unsigned char *buf = malloc((*size));\n"
  "    (void)memset(buf, 0, (*size));\n"
  "    fseek(file, curr_file_posi, SEEK_SET);\n"
  "    int read_size = (int)(fread(buf, 1, *size, file));\n"
  "    if (read_size != (*size)) {\n"
  "      printf(\"read file failed, total file size: %d, read_size: %d\\n\", (*size), read_size);\n"
  "      fclose(file);\n"
  "      free(buf);\n"
  "      return NULL;\n"
  "    }\n"
  "    fclose(file);\n"
  "    return (void *)buf;\n"
  "  } else {\n"
  "    printf(\"input data file should be .bin , .net\");\n"
  "    return NULL;\n"
  "  }\n"
  "}\n"
  "\n"
  "void SaveOutputData(char *final_name, unsigned char *output_data, unsigned int out_size) {\n"
  "  FILE *output_file;\n"
  "  output_file = fopen(final_name, \"w\");\n"
  "  if (output_file == NULL) {\n"
  "    printf(\"fopen output file: %s failed\\n\", final_name);\n"
  "    return;\n"
  "  }\n"
  "  unsigned char str[out_size];\n"
  "  for (unsigned int i = 0; i < out_size; ++i) {\n"
  "    str[i] = output_data[i];\n"
  "    fprintf(output_file, \"%d\\t\", str[i]);\n"
  "  }\n"
  "  fclose(output_file);\n"
  "}\n"
  "\n"
  "int ReadInputsFile(char *path, void **buffers, const int *inputs_size, int inputs_num) {\n"
  "  char *inputs_path[inputs_num];\n"
  "  char *delim = \",\";\n"
  "  char *token;\n"
  "  int i = 0;\n"
  "  while ((token = strtok_r(path, delim, &path))) {\n"
  "    if (i >= inputs_num) {\n"
  "      printf(\"inputs num is error, need: %d\\n\", inputs_num);\n"
  "      return -1;\n"
  "    }\n"
  "    inputs_path[i] = token;\n"
  "    printf(\"input %d: %s\\n\", i, inputs_path[i]);\n"
  "    i++;\n"
  "  }\n"
  "\n"
  "  for (i = 0; i < inputs_num; ++i) {\n"
  "    int size = 0;\n"
  "    buffers[i] = ReadInputData(inputs_path[i], &size);\n"
  "    if (size != inputs_size[i] || buffers[i] == NULL) {\n"
  "      printf(\"size mismatch, %s, %d, %d\\n\", inputs_path[i], size, inputs_size[i]);\n"
  "      return -1;\n"
  "    }\n"
  "  }\n"
  "  return 0;\n"
  "}\n";

#endif  // MICRO_LITE_MICRO_CODER_GENERATOR_CONST_BLOCKS_BENCH_LOAD_INPUT_H_
