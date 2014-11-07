/** ****************************************************************************
 *
 *  @file       esl_fs.h
 *  @brief      General file system API.
 *
 *  API for access to the filesystem. Provides some functions
 *  defined in MQX's shell module, simplified to our needs.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    2.4 2014-10-04: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Bugfix #124: fflush added for FS writes.
 *
 *  @version    2.3 2014-07-11: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Bugfix #166 (fs: esl_fs_ls does not return
 *                              number of files found).
 *
 *  @version    2.2 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    2.1 2013-12-14: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              All return values changed from int to uint_8.
 *
 *  @version    2.0 2013-11-30: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Module restructuring for ESL. New features
 *                              (cpdir, rmdir) introduced.
 *
 *  @version    1.3 2013-05-21: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Adaption for easyTool.
 *
 *  @version    1.2 2012-12-21: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Adaption for ns150.
 *
 *  @version    1.1 2012-02-10: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              lwshell renamed to fs.
 *
 *  @version    1.0 2012-01-18: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial lwshell version.
 *
 ******************************************************************************/
/*
 *  THIS SOFTWARE IS PROVIDED BY ELNICO "AS IS" AND ANY EXPRESSED OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL ELNICO OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *  THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef ESL_FS_H_984410215120
#define ESL_FS_H_984410215120
//******************************************************************************

#include "esl_fs_config.h"

#include <mqx.h>
#include <mfs.h>
#include <fio.h>

//******************************************************************************

enum {
  ESL_FS_OK = MQX_OK,
  ESL_FS_MODULE_OFF,
  ESL_FS_FSOPEN_FAIL,
  ESL_FS_FSOPEN_INVALID_ARG,
  ESL_FS_FSCLOSE_FAIL,
  ESL_FS_FOPEN_INVALID_ARG,
  ESL_FS_FOPEN_MFSALLOCPATH,
  ESL_FS_FOPEN_FOPEN,
  ESL_FS_CD_INVALID_ARG,
  ESL_FS_CD_FAIL,
  ESL_FS_LS_INVALID_ARG,
  ESL_FS_LS_MALLOC_FAIL,
  ESL_FS_LS_FILE_NOT_FOUND,
  ESL_FS_LS_FULLBUF,
  ESL_FS_LS_FIND_FIRST_FILE,
  ESL_FS_LS_FIND_NEXT_FILE,
  ESL_FS_PWD_INVALID_ARG,
  ESL_FS_PWD_MALLOC_FAIL,
  ESL_FS_PWD_IOCTL_FAIL,
  ESL_FS_CP_INVALID_ARG,
  ESL_FS_CP_READ,
  ESL_FS_CP_WRITE,
  ESL_FS_RM_INVALID_ARG,
  ESL_FS_RM_IOCTL_FAIL,
  ESL_FS_MKDIR_INVALID_ARG,
  ESL_FS_MKDIR_IOCTL_FAIL,
  ESL_FS_CPDIR_INVALID_ARG,
  ESL_FS_CPDIR_MFSALLOCPATH,
  ESL_FS_CPDIR_MEM_ALLOC,
  ESL_FS_CPDIR_GETFS_FAIL,
  ESL_FS_RMDIR_INVALID_ARG,
  ESL_FS_RMDIR_IOCTL_FAIL,
  ESL_FS_GETFS_INVALID_ARG,
  ESL_FS_GETFS_IO_GET_DEV_FOR_PATH,
  ESL_FS_GETFS_IO_GET_FS_BY_NAME,
  ESL_FS_REL2ABS_INVALID_ARG,
  ESL_FS_REL2ABS_MFSALLOCPATH,
  ESL_FS_REL2ABS_IOREL2ABS
};

//******************************************************************************

/** FileLite structure used e.g. as output of the ls command. */
typedef struct {
  uint_8    u8Attr;                     //!< File attributes.
  uint_32   u32Size;                    //!< File size.
  char      sName[SFILENAME_SIZE+1];    //!< File short name.
} ESL_FS_TFileLite;

//******************************************************************************
/** Opens filesystem and retrieves its handle for further operations.
 *  Use fs_closeFileSystem() to close it after the work.
 * @param [out] hFS  The filesystem handle will be stored here. This is
 *                           needed for further lwshell operations.
 * @param [in]  psDriveName  Drive name of the filesystem to open, e.g. "a:".
 * @param [out] err          Value returned by fopen() inside the function.
 *                           Check this value in case of failure.
 *                           Use MFS_Error_text(val) to get the meaning
 *                           of the returned code. Param may be NULL.
 * @return  ESL_FS_OK if the operation succeeds.
 *          ESL_FS_FSOPEN_INVALID_ARG if one of input pointers is NULL.
 *          ESL_FS_FSOPEN_FAIL on other fail. In this case, value
 *           stored in hFS may be undefined. */
uint_8 esl_fs_openFs (MQX_FILE_PTR *hFS, const char* psDriveName, _mqx_int *err);

//******************************************************************************
/** Closes filesystem. Frees the memory allocated for the given hFS.
 * @param [in]  hFS          The filesystem handle retrieved by esl_fs_openFs()
 *                           call.
 * @param [out] err          Value returned by fclose() inside the function.
 *                           Check this value in case of failure.
 *                           Use MFS_Error_text(val) to get the meaning
 *                           of the returned code. Param may be NULL.
 * @return  ESL_FS_OK if the operation succeeds.
 *          ESL_FS_FSCLOSE_FAIL on fail. In this case, value stored
 *           in hFS may be undefined. */
uint_8 esl_fs_closeFs (MQX_FILE_PTR hFS, _mqx_int *err);

//******************************************************************************

/** Opens a file specified by a relative path in the given filesystem.
 * @warning  Result of this method depends on the filesystem's current working
 *           directory. Be careful if working with the working directory from
 *           multiple tasks!
 * @param [in]  hFS          Handle to open filesystem in which the file to be
 *                           opened is located. Use esl_fs_openFs() to
 *                           retrieve this.
 * @param [out] fdFile       Pointer to the handle of the file, which was
 *                           opened by the function.
 * @param [in]  psFilePath   Both relative or absolute path, both separators
 *                           ('/', '\') are allowed. E.g. "fil1", "dir1/fil1",
 *                           "../fil3", "/dir4/fil5", "dir1\\fil2".
 * @param [out] err          Value adjusted in case of failure by commands
 *                           embedded in the function. Param may be NULL.
 * @return  ESL_FS_OK if the operation succeeds.
 *          ESL_FS_FOPEN_INVALID_ARG if one of input pointers is NULL.
 *          ESL_FS_FOPEN_MFSALLOCPATH in case of memory allocation problem,
 *          ESL_FS_FOPEN_FOPEN if file cannot be opened,
 *          other value in case fs_rel2abs fails (see documentation of that
 *          function. */
uint_8 esl_fs_fopen (MQX_FILE_PTR    hFS,
                     MQX_FILE_PTR  * fdFile,
                     const char    * psFilePath,
                     const char    * psMode,
                     _mqx_int      * err);

//******************************************************************************
/** Changes current directory on given filesystem.
 * @warning  Result of this method depends on the filesystem's current working
 *           directory. Be careful if working with the working directory from
 *           multiple tasks!
 * @param [in]  hFS          Handle to open filesystem to change its current
 *                           directory. Use esl_fs_openFs() to retrieve this.
 * @param [in]  psPath       Both relative or absolute path, both separators
 *                           ('/', '\') are allowed. E.g. "dir1", "dir1/dir2",
 *                           "../dir3", "/dir4/dir5", "dir1\\dir2".
 * @param [out] err          Value returned by ioctl() inside the function.
 *                           Check this value in case of failure. Explanation
 *                           for most probable errors: MFS_PATH_NOT_FOUND -
 *                           given directory does not exist.
 *                           MFS_INVALID_LENGTH_IN_DISK_OPERATION - given path
 *                           is longer then 260 characters. Possibly other MFS
 *                           errors may be returned, see <mfs.h>. Param may be
 *                           NULL.
 * @return  ESL_FS_OK if the operation succeeds.
 *          ESL_FS_CD_INVALID_ARG if hFS is NULL.
 *          ESL_FS_CD_FAIL on other failure. Check the value of err parameter
 *           in this case. */
uint_8 esl_fs_cd (MQX_FILE_PTR hFS, const char *psPath, _mqx_int *err);

//******************************************************************************

/** Lists current directory, i.e. provides names of files and folders with
 * additional info.
 *  It's possible to provide the output out via the paoFileArray parameter or to
 *  print to standard output.
 * @warning  Result of this method depends on the filesystem's current working
 *           directory. Be careful if working with the working directory from
 *           multiple tasks!
 * @param [in]  hFS          Handle to open filesystem to list its current
 *                           directory. Use esl_fs_openFs() to retrieve this.
 * @param [out] paoFileArray Array of ESL_FS_TFileLite objects, to which the
 *                           command output is stored. Use NULL to print the
 *                           command output to stdio.
 * @param [in]  u8ArraySize  Length of paoFileArray.
 * @param [in]  psWildcard   Wildcard input. Use "*" to list all files in the
 *                           current folder, "\*" to list the root, "\dir\*" to
 *                           list a directory, "*.xml" to list just XML files,
 *                           etc.
 * @param [in]  u8SearchAttr Attribute of files to list. Use e.g. MFS_SEARCH_ANY
 *                           for all files and folders, MFS_SEARCH_SUBDIR for
 *                           just directories, etc. See more in mfs.h.
 * @param [out] piRetCode    On success (ESL_FS_OK is returned), number of files
 *                           listed is stored here. On failure, error value is
 *                           stored here.
 * @return ESL_FS_OK on success. piRetCode stores the number of files listed.
 *         ESL_FS_LS_INVALID_ARG if hFS is NULL.
 *         ESL_FS_LS_FIND_FIRST_FILE if function fails to alloc needed temporary
 *         memory.
 *         ESL_FS_LS_FULLBUF if the output buffer is not large enough to print
 *         the whole result in. u8ArraySize files were listed, piRetCode stores
 *         the error details. */
uint_8 esl_fs_ls (const MQX_FILE_PTR    hFS,
                  ESL_FS_TFileLite    * paoFileArray,
                  uint_8                u8ArraySize,
                  const char          * psWildcard,
                  uint_8                u8SearchAttr,
                  _mqx_int            * piRetCode);

//******************************************************************************
/** Gets current working directory.
 * @warning  Result of this method depends on the filesystem's current working
 *           directory. Be careful if working with the working directory from
 *           multiple tasks!
 * @warning  Parameter psBuf needs to be at least 261 bytes long! If this
 *           condition is not satisfied, access violation may occur!
 * @param [in]  hFS          Handle to open filesystem to list its current
 *                           directory. Use esl_fs_openFs() to retrieve this.
 * @param [out] psBuf        Memory to print data to. This needs to be at least
 *                           261 bytes (since 260 chars is the maximum filepath
 *                           length)! If NULL, data is printed to standard
 *                           output.
 * @param [out] err          Value returned by ioctl() inside the function.
 *                           Check this value in case of failure (see <mfs.h>).
 *                           Param may be NULL.
 * @return ESL_FS_OK on success.
 *         ESL_FS_PWD_INVALID_ARG if hFS is NULL.
 *         ESL_FS_PWD_MALLOC_FAIL if function fails to alloc needed temporary
 *         memory. */
uint_8 esl_fs_pwd (const MQX_FILE_PTR hFS, char * psBuf, _mqx_int *err);

//******************************************************************************
/** Makes a copy of a file.
 * @warning  Result of this method depends on the filesystem's current working
 *           directory. Be careful if working with the working directory from
 *           multiple tasks!
 * @param [in]  hFS            Handle to open filesystem of the source file.
 *                             Use esl_fs_openFs() to retrieve this.
 * @param [in]  psSrcFilePath  Relative or absolute path to the source file.
 *                             Both separators ('/', '\') are allowed. Use e.g.
 *                             "fil1", "dir1/fil1", "../fil3", "/dir4/fil5",
 *                             "dir1\\fil2".
 * @param [in]  psDstFilePath  Relative or absolute path to the destination
 *                             file. This file must not exist! Both separators
 *                             ('/', '\') are allowed. Use e.g. "fil1",
 *                             "dir1/fil1", "../fil3", "/dir4/fil5",
 *                             "dir1\\fil2".
 * @param [out] err            Value can be adjusted by various embedded
 *                             functions in case of failure. Param may be NULL.
 * @return ESL_FS_OK on success.
 *         ESL_FS_CP_INVALID_ARG if hFS is NULL.
 *         ESL_FS_CP_READ if reading from the source file failes.
 *         ESL_FS_CP_WRITE if writing to the destinatino file failes.
 *         fs_fopen return value if that function failes. */
uint_8 esl_fs_cp (const MQX_FILE_PTR   hFS,
                  const char         * psSrcFilePath,
                  const char         * psDstFilePath,
                  _mqx_int           * err);

//******************************************************************************
/** Removes a file.
 * @warning  Result of this method depends on the filesystem's current working
 *           directory. Be careful if working with the working directory from
 *           multiple tasks!
 * @param [in]  hFS         Handle to open filesystem of the file to remove.
 *                          Use esl_fs_openFs() to retrieve this.
 * @param [in]  psFilePath  Relative or absolute path to the file to remove.
 *                          Both separators ('/', '\') are allowed. Use e.g.
 *                          "fil1", "dir1/fil1", "../fil3", "/dir4/fil5",
 *                          "dir1\\fil2".
 * @param [out] err         Value returned by ioctl call in case of its failure.
 *                          Param may be NULL.
 * @return ESL_FS_OK on success.
 *         ESL_FS_RM_INVALID_ARG if hFS is NULL.
 *         ESL_FS_RM_IOCTL_FAIL if reading from the source file failes. */
uint_8 esl_fs_rm (const MQX_FILE_PTR hFS, const char* psFilePath, _mqx_int *err);

//******************************************************************************
/** Creates a directory.
 * @warning  Result of this method depends on the filesystem's current working
 *           directory. Be careful if working with the working directory from
 *           multiple tasks!
 * @param [in]  hFS         Handle to open filesystem where the dir shall be
 *                          created. Use esl_fs_openFs() to retrieve this.
 * @param [in]  psDirPath   Relative or absolute path to the directory to create.
 *                          Both separators ('/', '\') are allowed. Use e.g.
 *                          "dir1", "dir1/dir2", "../dir3", "/dir4/dir5",
 *                          "dir1\\dir2".
 * @param [out] err         Value returned by ioctl call in case of its failure.
 *                          Param may be NULL.
 * @return ESL_FS_OK on success.
 *         ESL_FS_MKDIR_INVALID_ARG if hFS is NULL.
 *         ESL_FS_MKDIR_IOCTL_FAIL if reading from the source file failes. */
uint_8 esl_fs_mkdir (const MQX_FILE_PTR hFS, const char* psDirPath, _mqx_int *err);

//******************************************************************************

//******************************************************************************
/** Copy a directory with all its contents from source path to destination path.
 * @warning  Result of this method depends on the filesystem's current working
 *           directory. Be careful if working with the working directory from
 *           multiple tasks!
 * @param [in]  hFS            Handle to open filesystem of source directory.
 *                             Use esl_fs_openFs() to retrieve this.
 * @param [in]  psSrcDirPath   Relative or absolute path to source directory.
 *                             Both separators ('/', '\') are allowed. Use e.g.
 *                             "dir1", "dir1/dir2", "../dir3", "/dir4/dir5",
 *                             "dir1\\dir2".
 * @param [in]  psDstFilePath  Relative or absolute path to the destination
 *                             directory. This file must not exist! Both
 *                             separators ('/', '\') are allowed. Use e.g.
 *                             "dir1", "dir1/dir2", "../dir3", "/dir4/dir5",
 *                             "dir1\\dir2".
 * @param [out] err            Value returned by ioctl call in case of its
 *                             failure. Param may be NULL.
 * @return                     ESL_FS_OK on success, other ESL_FS_* value on
 *                             failure. */
uint_8 esl_fs_cpdir(const MQX_FILE_PTR   hFS,
                    const char         * psSrcDirPath,
                    const char         * psDstDirPath,
                    _mqx_int           * err);

//******************************************************************************
/** Remove a subdirectory.
 * @warning  Result of this method depends on the filesystem's current working
 *           directory. Be careful if working with the working directory from
 *           multiple tasks!
 * @param [in]  hFS         Handle to open filesystem of the dir to be removed.
 *                          Use esl_fs_openFs() to retrieve this.
 * @param [in]  psDirPath   Relative or absolute path to the directory to remove.
 *                          Both separators ('/', '\') are allowed. Use e.g.
 *                          "dir1", "dir1/dir2", "../dir3", "/dir4/dir5",
 *                          "dir1\\dir2".
 * @param [out] err         Value returned by ioctl call in case of its failure.
 *                          Param may be NULL.
 * @return ESL_FS_OK on success.
 *         ESL_FS_RMDIR_INVALID_ARG if hFS is NULL.
 *         ESL_FS_RMDIR_IOCTL_FAIL if reading from the source file failes. */
uint_8 esl_fs_rmdir (const MQX_FILE_PTR hFS, const char* psDirPath, _mqx_int *err);

//******************************************************************************

/** Gets the file system handle from an input absolute path.
 * Hint: It's not possible to call this function for input relative paths!
 * @param [in]  psAbsPath    Input absolute path including the device name.
 * @param [out] err          Check this value in case of a function failure.
 * @return  File system handle on success, NULL on failure. */
MQX_FILE_PTR esl_fs_getFs (const char* psAbsPath, _mqx_int *err);

//******************************************************************************

/** Converts the input relative path string to the absolute one.
 * @warning  Result of this method depends on the filesystem's current working
 *           directory. Be careful if working with the working directory from
 *           multiple tasks!
 * @warning  Parameter psAbsPath needs to be at least 261 bytes long! If this
 *           condition is not satisfied, access violation may occur!
 * @param [in]  hFS          Handle to open filesystem in which the file
 *                           specified by psRelPath is located. Use
 *                           esl_fs_openFs() to retrieve this.
 * @param [out] psAbsPath    Memory to print the output absolute path to. This
 *                           needs to be at least 261 bytes (since 260 chars is
 *                           the maximum filepath length)!
 * @param [in]  psRelPath    String containing the input relative path.
 * @param [out] err          Value returned by ioctl() inside the function.
 *                           Check this value in case of failure (see <mfs.h>).
 *                           Param may be NULL.
 * @return ESL_FS_OK on success.
 *         ESL_FS_REL2ABS_INVALID_ARG if one of input pointers is NULL.
 *         ESL_FS_REL2ABS_MFSALLOCPATH in case of memory allocation problems.
 *         Other value in case of failure of fs_pwd or _io_rel2abs (MFS). */
uint_8 esl_fs_rel2abs (const MQX_FILE_PTR    hFS,
                       char                * psAbsPath,
                       const char          * psRelPath,
                       _mqx_int            * err);

//******************************************************************************

#endif /* ESL_FS_H_984410215120 */
