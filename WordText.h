#pragma once


// -------------  FUNCTION 1 ------------------------------
// ------- PUT TITLE IN BOX TABLE -------------------------
// --------------------------------------------------------
void titlebox(char* c)
{
	int L_up_corner = 201;
	int R_up_corner = 187;
	int L_dn_corner = 200, R_dn_corner = 188;
	int h_Line = 205, vLine = 186;
	int i = strlen(c);

	printf("%c", L_up_corner);
	for (int j = 0; j < i + 1; j++)printf("%c", h_Line);
	printf("%c\n", R_up_corner);

	printf("%c%s %c\n", vLine, c, vLine);


	printf("%c", L_dn_corner);
	for (int j = 0; j < i + 1; j++)printf("%c", h_Line);
	printf("%c\n", R_dn_corner);

}
//--------------------------------------------------------------------

//-------------  FUNCTION 2 -------------------------------------------------
// put them in string array W[][], and gave more information about that string

int wordofstring1(const char* c, char W[12][15])
{
	int i = 0, j = 0, b = 0;
	char* s; s = c;
	do
	{
		if (*s == ' ')
		{
			b++;
			if (*(s + 1) != ' ')
			{
				if (j != 0)
				{
					W[i][j] = '\0'; j = 0; i++;
				}
			}
		}
		else
		{
			W[i][j] = *s;
			j++;
		}

	} while (*(s++) != '\0');
	if (W[i][0] == '\0') i = i - 1;
	return i;
}
//-------------------- FUNCTION 3 ------------------------------------
// best version of extraction word from string or text and put it in word array--------------

int wordofstr(const char* c, char w[12][15])
{
	char ch;
	char* s;
	int b;
	int i = 0, j = 0;


	//extract only word with alphabet;
	s = c;
	while (*s != '\0')
	{
		b = 0;
		for (ch = 65; ch < 91; ch++)
		{
			if ((*s == ch) || (*s == (ch + 32)))
			{
				w[i][j] = *s; j++; b = 1; break;
			}
		}

		if (b == 0) {
			if (j == 0)
			{
				j = 0;
			}
			else {
				w[i][j] = '\0';
				i++;
				j = 0;
			}
		}


		s++;
	}
	w[i][j] = '\0';
	if (w[i][0] == '\0') i--;
	return i;
}

//------------------------- END FUNCTION ----------------------------------------------------
//-------------------------------------------------------------------------------------------
