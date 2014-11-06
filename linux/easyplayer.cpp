#include "easyplayer.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//******************************************************************************

#define CMD_MAXLEN                      500
#define CMD_MAXARGS                     40

//******************************************************************************

EasyPlayer::EasyPlayer (QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
}

//******************************************************************************

EasyPlayer::~EasyPlayer()
{
  printf("~EasyPlayer\n");
}

//******************************************************************************

void EasyPlayer::play (const QString & sPipeline)
{
  this->showFullScreen();

  m_gstPid = this->execGst(sPipeline);
  if (-1 == m_gstPid) {
    printf("EasyPlayer: fork failed\n");
  } else {
    printf("EasyPlayer: Gst process pid=%d\n", m_gstPid);
  }
}

//******************************************************************************

pid_t EasyPlayer::execGst (const QString & sPipeline)
{
  pid_t pid = fork();

  if (0 == pid) {                                                               // CHILD process
    // redirect child's output to the file
    int fd = open("player.log", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) return pid;
    dup2(fd, 1);                        // make stdout go to file
    dup2(fd, 2);                        // make stderr go to file
    ::close(fd);                        // fd no longer needed - the dup'ed handles are sufficient
    // execute Gst
    EasyPlayer::execute("/usr/bin/gst-launch", sPipeline.toStdString().c_str());
    exit(EXIT_FAILURE);                 // we should not get here, execute never returns

  } else {                                                                      // PARENT process or fork failure (-1)
    return pid;
  }
}

//******************************************************************************

void EasyPlayer::execute (const char * sFilename, const char * sArguments)
{
  char          sArgsBuf  [CMD_MAXLEN];
  char        * argv      [CMD_MAXARGS];
  int           i;

  strncpy(sArgsBuf, sArguments, CMD_MAXLEN);
  argv[0] = (char*)sFilename;

  i = 1;
  argv[i] = strtok(sArgsBuf, " ");
  while ((argv[i] != NULL) && (i < CMD_MAXARGS-1)) {
    argv[++i] = strtok(NULL, " ");
  }

  execvp(sFilename,  argv);
}

//******************************************************************************

void EasyPlayer::killGst (void)
{
  if (-1 != m_gstPid) kill(m_gstPid, SIGINT);
  wait(NULL);
  this->close();
}

//******************************************************************************
