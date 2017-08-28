<?php
/**
 * Posts extender: Youtube URL converter for post contents
 *
 * @var post_record $record
 * 
 * @package    BardCanvas
 * @subpackage youtube_for_bardcanvas
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

use hng2_modules\posts\post_record;

include_once ROOTPATH . "/lib/phpQuery-onefile.php";

global $config, $record;

$contents = $config->globals["processing_contents"];

$pq = phpQuery::newDocumentHTML($contents, "utf-8");

foreach($pq->find("a.youtube_link") as $a)
{
    $a    = pq($a);
    $href = $a->attr("href");
    
    preg_match_all('/\b((https:\/\/)?(www\.)?youtube\.com\/watch\?v=([a-z0-9\-_]+)(&(t=\d+))?)|((https:\/\/)?youtu\.be\/([a-z0-9\-_]+)(\?(t=\d+))?)\b/i', $href, $matches);
    # echo "<pre class='framed_content'>" . print_r($matches, true) . "</pre>";
    
    if( empty($matches[4]) && empty($matches[9]) ) continue;
    
    $id = empty($matches[4][0]) ? $matches[9][0] : $matches[4][0];
    
    $search = $a->htmlOuter();
    $html   = "<p class='youtube_container'><iframe class='youtube_video' src='https://www.youtube.com/embed/$id' frameborder='0' allowfullscreen></iframe></p>";
    
    $contents = str_replace($search, $html, $contents);
}

$config->globals["processing_contents"] = $contents;
