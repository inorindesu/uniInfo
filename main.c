/* 
 * uniInfo
 *
 * Provide unicode string information as provided in glib
 *
 * Copyright (C) 2013  Inori Sakura <inorindesu@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include <glib.h>
#include <string.h>
#include <unistd.h>

bool parseArgs(int argc, char** argv, bool* normalize,
               char* input_buffer, int input_buffer_size,
               bool* addSpace)
{
  bool buffer_set = false;
  for(int i = 1; i < argc; i++)
    {
      if (strcmp(argv[i], "-n") == 0)
        {
          *normalize = true;
        }
      else if (strcmp(argv[i], "-a") == 0)
        {
          *addSpace = true;
        }
      else if(buffer_set == false)
        {
          if (strlen(argv[i]) < input_buffer_size)
            {
              strcpy(input_buffer, argv[i]);
              buffer_set = true;
            }
        }
    }
  return buffer_set;
}

void print_usage()
{
  printf("Usage\n");
  printf("  uniInfo -n MY_STRING\n\t\tPrint information of normalized MY_STRING\n");
  printf("  uniInfo MY_STRING\n\t\tPrint information MY_STRING\n");
  printf("\n\nSwitches\n");
  printf("Switches:");
  printf("  -n    Normalize input before analyze the string\n");
  printf("  -a    Add space on 'Char' column.\n");
  printf("        This makes some characters (e.g. vowel marks of Tibetan text)");
  printf("         more clear when you viewing the result");
}

char* get_type_string(GUnicodeType type)
{
  switch(type)
    {
    case G_UNICODE_CONTROL:
      return "Control";
    case G_UNICODE_FORMAT:
      return "Format";
    case G_UNICODE_UNASSIGNED:
      return "Unassigned";
    case G_UNICODE_PRIVATE_USE:
      return "Private use";
    case G_UNICODE_SURROGATE:
      return "Surrogate";
    case G_UNICODE_LOWERCASE_LETTER:
      return "Lowercase letter";
    case G_UNICODE_MODIFIER_LETTER:
      return "Modifier letter";
    case G_UNICODE_OTHER_LETTER:
      return "Other letter";
    case G_UNICODE_TITLECASE_LETTER:
      return "Titlecase letter";
    case G_UNICODE_UPPERCASE_LETTER:
      return "Uppercase letter";
    case G_UNICODE_SPACING_MARK:
      return "Spacing mark";
    case G_UNICODE_ENCLOSING_MARK:
      return "Enclosing mark";
    case G_UNICODE_NON_SPACING_MARK:
      return "Non-spacing mark";
    case G_UNICODE_DECIMAL_NUMBER:
      return "Decimal number";
    case G_UNICODE_LETTER_NUMBER:
      return "Letter number";
    case G_UNICODE_OTHER_NUMBER:
      return "Other number";
    case G_UNICODE_CONNECT_PUNCTUATION:
      return "Connect punctuation";
    case G_UNICODE_DASH_PUNCTUATION:
      return "Dash punctuation";
    case G_UNICODE_CLOSE_PUNCTUATION:
      return "Close punctuation";
    case G_UNICODE_FINAL_PUNCTUATION:
      return "Final punctuation";
    case G_UNICODE_INITIAL_PUNCTUATION:
      return "Initial punctuation";
    case G_UNICODE_OTHER_PUNCTUATION:
      return "Other punctuation";
    case G_UNICODE_OPEN_PUNCTUATION:
      return "Open punctuation";
    case G_UNICODE_CURRENCY_SYMBOL:
      return "Currency symbol";
    case G_UNICODE_MODIFIER_SYMBOL:
      return "Modifier symbol";
    case G_UNICODE_MATH_SYMBOL:
      return "Math symbol";
    case G_UNICODE_OTHER_SYMBOL:
      return "Other symbol";
    case G_UNICODE_LINE_SEPARATOR:
      return "Line separator";
    case G_UNICODE_PARAGRAPH_SEPARATOR:
      return "Paragraph separator";
    case G_UNICODE_SPACE_SEPARATOR:
      return "Space separator";
    default:
      return "??";
    }
}

char* get_break_type_string(GUnicodeBreakType type)
{
  switch(type)
    {
    case G_UNICODE_BREAK_MANDATORY:
      return "Mandatory";
    case G_UNICODE_BREAK_CARRIAGE_RETURN:
      return "Cr";
    case G_UNICODE_BREAK_LINE_FEED:
      return "Lf";
    case G_UNICODE_BREAK_COMBINING_MARK:
      return "Combining mark";
    case G_UNICODE_BREAK_SURROGATE:
      return "Surrogate";
    case G_UNICODE_BREAK_ZERO_WIDTH_SPACE:
      return "Zero-width space";
    case G_UNICODE_BREAK_INSEPARABLE:
      return "Inseparable";
    case G_UNICODE_BREAK_NON_BREAKING_GLUE:
      return "Non-breaking glue";
    case G_UNICODE_BREAK_CONTINGENT:
      return "Contingent";
    case G_UNICODE_BREAK_SPACE:
      return "Space";
    case G_UNICODE_BREAK_AFTER:
      return "After";
    case G_UNICODE_BREAK_BEFORE:
      return "Before";
    case G_UNICODE_BREAK_BEFORE_AND_AFTER:
      return "Before and after";
    case G_UNICODE_BREAK_HYPHEN:
      return "Hyphen";
    case G_UNICODE_BREAK_NON_STARTER:
      return "Non-starter";
    case G_UNICODE_BREAK_OPEN_PUNCTUATION:
      return "Open punctuation";
    case G_UNICODE_BREAK_CLOSE_PUNCTUATION:
      return "Close punctuation";
    case G_UNICODE_BREAK_QUOTATION:
      return "Quotation";
    case G_UNICODE_BREAK_EXCLAMATION:
      return "Exclamation";
    case G_UNICODE_BREAK_IDEOGRAPHIC:
      return "Ideographic";
    case G_UNICODE_BREAK_NUMERIC:
      return "Numeric";
    case G_UNICODE_BREAK_INFIX_SEPARATOR:
      return "Infix separator";
    case G_UNICODE_BREAK_SYMBOL:
      return "Break symbol";
    case G_UNICODE_BREAK_ALPHABETIC:
      return "Break alphabetic";
    case G_UNICODE_BREAK_PREFIX:
      return "Break prefix";
    case G_UNICODE_BREAK_POSTFIX:
      return "Break posfix";
    case G_UNICODE_BREAK_COMPLEX_CONTEXT:
      return "Complex content";
    case G_UNICODE_BREAK_AMBIGUOUS:
      return "Break ambiguous";
    case G_UNICODE_BREAK_NEXT_LINE:
      return "Next line";
    case G_UNICODE_BREAK_WORD_JOINER:
      return "Word jointer";
    case G_UNICODE_BREAK_HANGUL_L_JAMO:
      return "Hangul L Jamo";
    case G_UNICODE_BREAK_HANGUL_V_JAMO:
      return "Hangul V Jamo";
    case G_UNICODE_BREAK_HANGUL_T_JAMO:
      return "Hangul T Jamo";
    case G_UNICODE_BREAK_HANGUL_LV_SYLLABLE:
      return "Hangul LV Syllable";
    case G_UNICODE_BREAK_HANGUL_LVT_SYLLABLE:
      return "Hangul LVT Syllable";
    case G_UNICODE_BREAK_CLOSE_PARANTHESIS:
      return "Close paranthesis";
    case G_UNICODE_BREAK_CONDITIONAL_JAPANESE_STARTER:
      return "Conditional Japanese starter";
    case G_UNICODE_BREAK_HEBREW_LETTER:
      return "Hebrew letter";
    case G_UNICODE_BREAK_REGIONAL_INDICATOR:
      return "Regional indicator";
    default:
    case G_UNICODE_BREAK_UNKNOWN:
      return "??";
    } 
}

void put_script(int script)
{
  char* scriptBuf = (char*)&script;
  for(int i = 3; i >= 0; i--)
    {
      putchar(scriptBuf[i]);
    }
}

int main(int argc, char** argv)
{
  /* Get max command line size*/
  int max_command_line_size = sysconf(_SC_ARG_MAX);
  fprintf(stderr, "Max command line size is %d\n", max_command_line_size);
  
  /* parse command line arguments */
  bool normalize = false;
  bool addSpace = false;
  char* buf = g_malloc0(max_command_line_size + 1);
  if (parseArgs(argc, argv, &normalize, buf, max_command_line_size, &addSpace) == false)
    {
      print_usage();
      return -1;
    }
  fprintf(stderr, "Input is set");
  if (normalize)
    fprintf(stderr, " and will be normalized.\n");
  else
    fprintf(stderr, ".\n");
  
  if (addSpace)
    fprintf(stderr, "Space will be added on characters for clarification\n");
  
  /* Process input */
  fprintf(stderr, "Validating\n");
  if (g_utf8_validate(buf, -1, NULL) == false)
    {
      fprintf(stderr, "ERROR: input is not valid UTF8 string!\n");
      return -1;
    }
  
  if (normalize)
    {
      fprintf(stderr, "Normalizing\n");
      char* normalized = g_utf8_normalize(buf, -1, G_NORMALIZE_DEFAULT);
      if (normalized == NULL)
        {
          fprintf(stderr, "ERROR: during normalization\n");
          return -1;
        }
      g_free(buf);
      buf = normalized;
    }
  
  fprintf(stderr, "To ucs4 for convenience\n");
  glong itemsWritten = -1;
  gunichar* ucs4_buffer = g_utf8_to_ucs4(buf, -1, NULL, &itemsWritten, NULL);
  fprintf(stderr, "%d chars converted\n", itemsWritten);
  if (ucs4_buffer == NULL)
    {
      fprintf(stderr, "ERROR: when converting to ucs4 string\n");
      return -1;
    }
  
  int index = 0;
  gunichar currentChar = 0;
  fprintf(stderr, "Writing output\n");
  if (normalize)
    {
      printf("# Normalized input string\n");
    }
  else
    {
      printf("# Original input string\n");
    }
  
  printf("#Char index\tChar\tScript\tType\tBreakType\n");
  
  const int singleUni8Size = 6 + 1;
  gchar* charBuf = g_malloc0(singleUni8Size);
  gchar dottedCircle[] = {0xE2, 0x97, 0x8c, 0};
  while((currentChar = ucs4_buffer[index]) != 0)
    {
      /*clearing*/
      memset(charBuf, 0, singleUni8Size);
      
      g_unichar_to_utf8(currentChar, charBuf);
      if (addSpace)
        {
          printf("%d\t  %s\t", index, charBuf);
        }
      else
        {
          if (g_unichar_ismark(currentChar))
            printf("%d\t%s%s\t", index, dottedCircle, charBuf);
          else
            printf("%d\t%s\t", index, charBuf);
        }
      put_script(g_unicode_script_to_iso15924(g_unichar_get_script(currentChar)));
      printf("\t%s\t%s\n",
             get_type_string(g_unichar_type(currentChar)),
             get_break_type_string(g_unichar_break_type(currentChar))
             );

      index += 1;
    }
}
