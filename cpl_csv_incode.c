/**********************************************************************
 * $Id: cpl_csv_incode.c,v 1.8 2007/07/20 18:08:29 fwarmerdam Exp $
 *
 * Name:     cpl_struct.c
 * Project:  libgeotiff
 * Purpose:  Provide "CSV API" interface to in-code EPSG CSV tables.
 * Author:   Derrick J Brashear <shadow@dementia.org>
 *
 ******************************************************************************
 * Copyright (c) 1999, Frank Warmerdam
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************
 *
 * $Log: cpl_csv_incode.c,v $
 * Revision 1.8  2007/07/20 18:08:29  fwarmerdam
 * Handle unexpected .csv files, and missing records more gracefully.
 *
 * Revision 1.7  2004/03/23 18:21:56  warmerda
 * Added CSVReadParseLine() stub
 *
 * Revision 1.6  2003/01/20 21:42:52  warmerda
 * Ensure CSVGetField() does not crash if record not found.
 *
 * Revision 1.5  2003/01/20 07:11:04  warmerda
 * updated csv-incode support to 6.2.2
 *
 * Revision 1.4  2002/06/19 03:51:15  warmerda
 * migrated cpl_csv.h into cpl_serv.h
 *
 * Revision 1.3  2002/02/11 14:22:22  warmerda
 * Added stub CSVDeaccess().
 *
 * Revision 1.2  2001/06/28 17:53:20  warmerda
 * Use EQUAL instead of strcasecmp() to ensure code builds on windows.
 * As per http://bugzilla.remotesensing.org/show_bug.cgi?id=59
 *
 * Revision 1.1  1999/12/10 18:00:58  warmerda
 * New
 *
 */

#include "cpl_serv.h"

#include "defs.h"

extern const datafile_rows_t *pcs_rows[];
extern const datafile_rows_t *gcs_rows[];
extern const datafile_rows_t *ellipsoid_rows[];
extern const datafile_rows_t *prime_meridian_rows[];
extern const datafile_rows_t *datum_rows[];
extern const datafile_rows_t *unit_of_measure_rows[];
extern const datafile_rows_t *projop_wparm_rows[];


/* Pointers to data */
static const datafile_t files[] = {
  { "pcs", pcs_rows },
  { "gcs", gcs_rows },
  { "ellipsoid", ellipsoid_rows },
  { "prime_meridian", prime_meridian_rows },
  { "datum", datum_rows },
  { "unit_of_measure", unit_of_measure_rows },
  { "projop_wparm", projop_wparm_rows },
  { NULL, NULL }
};

#if 0
main()
{
  datafile_t *csvfile;
  char **papszRecord;
  int i, row, col;

  papszRecord = CSVScanFileByName( "horiz_cs.csv", "HORIZCS_CODE",
				   "2200", CC_Integer );

  printf ("%s %s\n", papszRecord[0], papszRecord[1]);
  csvfile = &files[0];
  while (csvfile->name != NULL) {
    printf("file name is %s\n", csvfile->name);
    for (i = 0; csvfile->cols[i]; i++) {
      printf("column name is %s\n", csvfile->cols[i]);
      row = 1; col = 0;
      if (csvfile->rows[row] && csvfile->rows[row][col])
	printf("value %d,%d is %s\n", row, col, csvfile->rows[row][col]);
    }
    csvfile++;
  }
}
#endif

const char * CSVFilename( const char *pszBasename )
{
  return pszBasename;
}

static int CSVCompare( const char * pszFieldValue, const char * pszTarget,
                       CSVCompareCriteria eCriteria )
{
    if( eCriteria == CC_ExactString )
    {
        return( !EQUAL( pszFieldValue, pszTarget ) == 0 );
    }
    else if( eCriteria == CC_ApproxString )
    {
        return( !EQUAL( pszFieldValue, pszTarget ) );
    }
    else if( eCriteria == CC_Integer )
    {
        return( atoi(pszFieldValue) == atoi(pszTarget) );
    }
    return FALSE;
}

void CSVDeaccess( const char *pszFilename )
{
}

static int __CSVGetFileId( const char * pszFilename)
{
  datafile_t *csvfile;
  int i = 0;

  csvfile = (datafile_t *)&files[i];
  for (i = 0; csvfile->name; i++, csvfile = (datafile_t *)&files[i])
  {
    if (!strncmp(csvfile->name,pszFilename,(strlen(pszFilename)-4)))
      return i;
  }

  return -1;
}

char **CSVScanFileByName( const char * pszFilename,
                          const char * pszKeyFieldName,
                          const char * pszValue, 
                          CSVCompareCriteria eCriteria )
{
  datafile_t *csvfile;
  int row, col, iFile;

  iFile = __CSVGetFileId(pszFilename);
  if( iFile == -1 )
      return NULL;

  col = CSVGetFileFieldId(pszFilename, pszKeyFieldName);

  csvfile = (datafile_t *)&files[iFile];
  for (row = 1; ((csvfile->rows[row] != 0) && (csvfile->rows[row][col] != 0));
       row++) {
    if (CSVCompare(csvfile->rows[row][col], pszValue, eCriteria))
      return ((char **)csvfile->rows[row]);
  }

  return NULL;
}

int CSVGetFileFieldId( const char * pszFilename, const char * pszFieldName)
{
    datafile_t *csvfile;
    int i, iFile;

    iFile = __CSVGetFileId(pszFilename);
    if( iFile == -1 )
        return -1;

    csvfile = (datafile_t *)&files[iFile];
    if (!strncmp(csvfile->name,pszFilename,(strlen(pszFilename)-4)))
    {
        for (i = 0; csvfile->rows[0][i]; i++) 
            if (EQUAL(pszFieldName, csvfile->rows[0][i]))
                return i;
    }

    return -1;
}

const char *CSVGetField( const char * pszFilename,
                         const char * pszKeyFieldName,
                         const char * pszKeyFieldValue,
                         CSVCompareCriteria eCriteria,
                         const char * pszTargetField )
{
  char **papszRecord;
  int  iField;

  papszRecord = CSVScanFileByName( pszFilename, pszKeyFieldName,
				   pszKeyFieldValue, CC_Integer );

  if( papszRecord == NULL )
      return "";

  iField = CSVGetFileFieldId(pszFilename, pszTargetField);

  if( iField == -1 )
      return "";
  else
      return (papszRecord[iField]);
}

/* Dummy function */
void SetCSVFilenameHook( const char *(*pfnNewHook)( const char * ) )

{
}

/* dummy function */

char **CSVReadParseLine( FILE * fp )

{
    return NULL;
}
