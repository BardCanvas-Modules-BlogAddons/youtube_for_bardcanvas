<?php
/**
 * Posts extender: Youtube URL converter for post excerpts
 *
 * @var post_record $post
 * 
 * @package    BardCanvas
 * @subpackage youtube_for_bardcanvas
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

use hng2_modules\posts\post_record;

global $config, $post;

$contents = $config->globals["processing_contents"];

preg_match_all('/\b((https:\/\/)?(www\.)?youtube\.com\/watch\?v=([a-z0-9\-_]+)(&(t=\d+))?)|((https:\/\/)?youtu\.be\/([a-z0-9\-_]+)(\?(t=\d+))?)|((https:\/\/)?(www\.)?youtube\.com\/shorts\/([a-z0-9\-_]+))\b/i', $contents, $matches);

if( empty($matches[4]) && empty($matches[9]) && empty($matches[15]) ) return;

$id = $matches[4][0];
if( empty($id) ) $id = $matches[9][0];
if( empty($id) ) $id = $matches[15][0];

if( is_null($post) )
    $contents = "<div class='thumbnail'><img src='https://img.youtube.com/vi/$id/mqdefault.jpg'></div>";
else
    $contents = "<div class='thumbnail'><a href='{$post->get_permalink()}'><img src='https://img.youtube.com/vi/$id/mqdefault.jpg'></a></div>";

$config->globals["processing_contents"] = $contents;
