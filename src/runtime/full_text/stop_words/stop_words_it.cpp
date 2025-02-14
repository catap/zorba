/*
 * Copyright 2006-2016 zorba.io
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
#include "stdafx.h"

#include "utf8_chars.h"

namespace zorba {

//
// These words come from http://snowball.tartarus.org/.
//
extern char const *const stop_words_it[] = {
  "a",
  "abbia",
  "abbiamo",
  "abbiano",
  "abbiate",
  "ad",
  "agl",
  "agli",
  "ai",
  "al",
  "all",
  "alla",
  "alle",
  "allo",
  "anche",
  "avemmo",
  "avendo",
  "avesse",
  "avessero",
  "avessi",
  "avessimo",
  "aveste",
  "avesti",
  "avete",
  "aveva",
  "avevamo",
  "avevano",
  "avevate",
  "avevi",
  "avevo",
  "avr" agrave,
  "avrai",
  "avranno",
  "avrebbe",
  "avrebbero",
  "avrei",
  "avremmo",
  "avremo",
  "avreste",
  "avresti",
  "avrete",
  "avr" ograve,
  "avuta",
  "avute",
  "avuti",
  "avuto",
  "c",
  "che",
  "chi",
  "ci",
  "coi",
  "col",
  "come",
  "con",
  "contro",
  "cui",
  "da",
  "dagl",
  "dagli",
  "dai",
  "dal",
  "dall",
  "dalla",
  "dalle",
  "dallo",
  "degl",
  "degli",
  "dei",
  "del",
  "dell",
  "della",
  "delle",
  "dello",
  "di",
  "dov",
  "dove",
  "e",
  egrave,
  "ebbe",
  "ebbero",
  "ebbi",
  "ed",
  "era",
  "erano",
  "eravamo",
  "eravate",
  "eri",
  "ero",
  "essendo",
  "faccia",
  "facciamo",
  "facciano",
  "facciate",
  "faccio",
  "facemmo",
  "facendo",
  "facesse",
  "facessero",
  "facessi",
  "facessimo",
  "faceste",
  "facesti",
  "faceva",
  "facevamo",
  "facevano",
  "facevate",
  "facevi",
  "facevo",
  "fai",
  "fanno",
  "far" agrave,
  "farai",
  "faranno",
  "farebbe",
  "farebbero",
  "farei",
  "faremmo",
  "faremo",
  "fareste",
  "faresti",
  "farete",
  "far" ograve,
  "fece",
  "fecero",
  "feci",
  "fosse",
  "fossero",
  "fossi",
  "fossimo",
  "foste",
  "fosti",
  "fu",
  "fui",
  "fummo",
  "furono",
  "gli",
  "ha",
  "hai",
  "hanno",
  "ho",
  "i",
  "il",
  "in",
  "io",
  "l",
  "la",
  "le",
  "lei",
  "li",
  "lo",
  "loro",
  "lui",
  "ma",
  "mi",
  "mia",
  "mie",
  "miei",
  "mio",
  "ne",
  "negl",
  "negli",
  "nei",
  "nel",
  "nell",
  "nella",
  "nelle",
  "nello",
  "noi",
  "non",
  "nostra",
  "nostre",
  "nostri",
  "nostro",
  "o",
  "per",
  "perch" egrave,
  "pi" ugrave,
  "quale",
  "quanta",
  "quante",
  "quanti",
  "quanto",
  "quella",
  "quelle",
  "quelli",
  "quello",
  "questa",
  "queste",
  "questi",
  "questo",
  "sar" agrave,
  "sarai",
  "saranno",
  "sarebbe",
  "sarebbero",
  "sarei",
  "saremmo",
  "saremo",
  "sareste",
  "saresti",
  "sarete",
  "sar" ograve,
  "se",
  "sei",
  "si",
  "sia",
  "siamo",
  "siano",
  "siate",
  "siete",
  "sono",
  "sta",
  "stai",
  "stando",
  "stanno",
  "star" agrave,
  "starai",
  "staranno",
  "starebbe",
  "starebbero",
  "starei",
  "staremmo",
  "staremo",
  "stareste",
  "staresti",
  "starete",
  "star" ograve,
  "stava",
  "stavamo",
  "stavano",
  "stavate",
  "stavi",
  "stavo",
  "stemmo",
  "stesse",
  "stessero",
  "stessi",
  "stessimo",
  "steste",
  "stesti",
  "stette",
  "stettero",
  "stetti",
  "stia",
  "stiamo",
  "stiano",
  "stiate",
  "sto",
  "su",
  "sua",
  "sue",
  "sugl",
  "sugli",
  "sui",
  "sul",
  "sull",
  "sulla",
  "sulle",
  "sullo",
  "suo",
  "suoi",
  "ti",
  "tra",
  "tu",
  "tua",
  "tue",
  "tuo",
  "tuoi",
  "tutti",
  "tutto",
  "un",
  "una",
  "uno",
  "vi",
  "voi",
  "vostra",
  "vostre",
  "vostri",
  "vostro",

  0
};

} // namespace zorba
/* vim:set et sw=2 ts=2: */
