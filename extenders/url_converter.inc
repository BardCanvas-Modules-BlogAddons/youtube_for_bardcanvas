<?php
/**
 * Posts extender: Youtube URL converter for post contents
 *
 * @package    BardCanvas
 * @subpackage youtube_for_bardcanvas
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

include_once ROOTPATH . "/lib/phpQuery-onefile.php";

global $config;

$contents = $config->globals["processing_contents"];

$pq = phpQuery::newDocumentHTML($contents, "utf-8");

foreach($pq->find("a.youtube_link") as $a)
{
    $a    = pq($a);
    $href = $a->attr("href");
    
    preg_match_all('/\b((https:\/\/)?(www\.)?youtube\.com\/watch\?v=([a-z0-9\-_]+)(&(t=\d+))?)|((https:\/\/)?youtu\.be\/([a-z0-9\-_]+)(\?(t=\d+))?)|((https:\/\/)?(www\.)?youtube\.com\/shorts\/([a-z0-9\-_]+))\b/i', $href, $matches);
    # echo "<pre class='framed_content'>" . print_r($matches, true) . "</pre>";
    
    if( empty($matches[4]) && empty($matches[9]) && empty($matches[15]) ) continue;
    
    $id = $matches[4][0];
    if( empty($id) ) $id = $matches[9][0];
    if( empty($id) ) $id = $matches[15][0];
    
    $search = $a->htmlOuter();
    $html   = "<p class='youtube_container'><iframe class='youtube_video' data-video-id='$id'
                  src='https://www.youtube.com/embed/$id?feature=player_embedded'
                  frameborder='0' allowfullscreen></iframe></p>";
    
    $contents = str_replace($search, $html, $contents);
}

$config->globals["processing_contents"] = $contents;
