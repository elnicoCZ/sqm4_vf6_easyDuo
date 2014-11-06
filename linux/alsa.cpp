/*
 * alsa.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: petr
 */

#include "alsa.h"

#include <alsa/asoundlib.h>

void alsa_muteSpeaker (bool bMute)
{
  // Modified code from http://stackoverflow.com/questions/3985014/linux-alsa-sound-api-questions-how-do-you-mute
  snd_mixer_t           * handle;
  snd_mixer_selem_id_t  * pSid;
  snd_mixer_elem_t      * pElem;
  const char            * sCard = "default";
  const char            * sElemName = "Speaker Function";

  snd_mixer_open(&handle, 0);
  snd_mixer_attach(handle, sCard);
  snd_mixer_selem_register(handle, NULL, NULL);
  snd_mixer_load(handle);

  snd_mixer_selem_id_alloca(&pSid);
  snd_mixer_selem_id_set_index(pSid, 0);
  snd_mixer_selem_id_set_name(pSid, sElemName);
  pElem = snd_mixer_find_selem(handle, pSid);
  if (!pElem) printf("alsa_mute: Element '%s'  not found.\n", sElemName);

  if (pElem && snd_mixer_selem_is_enumerated(pElem)) {
    // 0 sets to "off", 1 sets to "on"
    snd_mixer_selem_set_enum_item (pElem, SND_MIXER_SCHN_MONO, !bMute);
  }

  snd_mixer_close(handle);
}
