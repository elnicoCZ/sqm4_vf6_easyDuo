/*
 * config.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: petr
 */

#include "config.h"

#include <iostream>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;

int config_loadMedia (QComboBox & oCombo, const char * sFilename)
{
  Config cfg;

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

      if (!(   video.lookupValue("name", sName)
            && video.lookupValue("pipeline", sPipeline))) {
        continue;
      }

      oCombo.addItem(sName.c_str(), sPipeline.c_str());
    }
  } catch (const SettingNotFoundException & e) {
    // ignore
  }

  return 0;
}
