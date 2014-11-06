/*
 * config.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: petr
 */

#include "config.h"

#include <iostream>
#include <limits.h>
#include <libconfig.h++>
#include <QList>

using namespace std;
using namespace libconfig;

int config_loadMedia (QComboBox & oCombo, const char * sFilename)
{
  Config cfg;

  QIcon qIcnVideo(":/icons/movie");
  QIcon qIcnCamera(":/icons/webcam");

  // read and parse the file
  try {
    cfg.readFile(sFilename);
  } catch (const FileIOException & e) {
    puts("I/O error while reading file.");
    return 1;
  } catch (const ParseException & e) {
    printf("Parse error at %s: %d - %s\n",
           e.getFile(), e.getLine(), e.getError());
    return 2;
  }


  const Setting & root = cfg.getRoot();

  // all video pipelines
  try {
    const Setting & videos  = root["media"]["video"];
    int             cnt     = videos.getLength();

    for (int i=0; i<cnt; ++i) {
      const Setting & video = videos[i];
      string          sName;
      string          sPipeline;
      QList<QVariant> qList;

      if (!(   video.lookupValue("name", sName)
            && video.lookupValue("pipeline", sPipeline))) {
        continue;
      }

      qList.append(sPipeline.c_str());
      oCombo.addItem(qIcnVideo, sName.c_str(), qList);
    }
  } catch (const SettingNotFoundException & e) {
    // ignore
  }

  // all camera pipelines
  try {
    const Setting & cameras = root["media"]["camera"];
    int             cnt     = cameras.getLength();

    for (int i=0; i<cnt; ++i) {
      const Setting & camera = cameras[i];
      string          sName;
      string          sPipeline;
      string          sCheck;
      QList<QVariant> qList;

      if (!(   camera.lookupValue("name", sName)
            && camera.lookupValue("pipeline", sPipeline))) {
        continue;
      }

      if (i==0) oCombo.insertSeparator(INT_MAX);

      qList.append(sPipeline.c_str());
      if (camera.lookupValue("check", sCheck)) qList.append(sCheck.c_str());
      oCombo.addItem(qIcnCamera, sName.c_str(), qList);
    }
  } catch (const SettingNotFoundException & e) {
    // ignore
  }

  return 0;
}
