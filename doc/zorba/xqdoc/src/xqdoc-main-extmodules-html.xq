import module namespace x2h = "http://www.zorba-xquery.com/modules/xqdoc2xhtml/";

declare variable $modulePath          as xs:string external;
declare variable $xhtmlRequisitesPath as xs:string external;
declare variable $xqdocBuildPath      as xs:string external;
declare variable $examplePath         as xs:string external;
declare variable $zorbaVersion        as xs:string external;



x2h:copy-xhtml-requisites($modulePath,
                          $xhtmlRequisitesPath,
                          fn:trace($xqdocBuildPath,"Copy XHTML requisites in:"));
                          

variable $indexHtmlPath as xs:string := 
fn:concat($xhtmlRequisitesPath, "/templates/main.html");

x2h:main( $modulePath,
          $xqdocBuildPath,
          $indexHtmlPath,
          $examplePath,
          $zorbaVersion,
          $xhtmlRequisitesPath);