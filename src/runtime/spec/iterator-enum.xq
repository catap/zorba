(:
 : Copyright 2006-2016 zorba.io
 :
 : Licensed under the Apache License, Version 2.0 (the "License");
 : you may not use this file except in compliance with the License.
 : You may obtain a copy of the License at
 :
 : http://www.apache.org/licenses/LICENSE-2.0
 :
 : Unless required by applicable law or agreed to in writing, software
 : distributed under the License is distributed on an "AS IS" BASIS,
 : WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 : See the License for the specific language governing permissions and
 : limitations under the License.
:)

declare namespace zorba="http://www.zorba-xquery.com";

import module namespace file = "http://expath.org/ns/file";
import module namespace gen = "http://www.zorba-xquery.com/internal/gen" at "utils.xq";

declare variable $files as xs:string external;

declare variable $iterators := 
    for $doc in tokenize($files,',')
    return fn:parse-xml(file:read-text($doc))//zorba:iterator/@name;

let $enums := for $iter in $iterators
              return if ($iter eq "") then () else concat("TYPE_", $iter)
return
  string-join(
    (
      gen:add-copyright(),
      for $enum in $enums
      return concat($gen:indent, $enum, ','),
      $gen:newline,
      $gen:newline
    ),
    $gen:newline)
