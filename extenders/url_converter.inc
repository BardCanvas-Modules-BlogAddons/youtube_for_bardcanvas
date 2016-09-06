<?php
/**
 * Posts extender: Youtube URL converter for post excerpts
 *
 * @var post_record $record
 * 
 * @package    BardCanvas
 * @subpackage external_usertags
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

use hng2_modules\posts\post_record;

global $config, $record;

$contents = $config->globals["processing_contents"];

# Unlinking
preg_match_all('/<a.*>.*<\/a>/i', $contents, $matches);
if( count($matches) > 0 )
{
    foreach($matches[0] as $match)
    {
        if( preg_match('/(youtube\.com|youtu\.be)/i', $match) )
        {
            try {
                $a = new SimpleXMLElement($match);
                $contents = str_replace($match, trim($a["href"]), $contents);
            } catch(\Exception $e) {
                continue;
            }
        }
    }
}

preg_match_all('/\b((https:\/\/)?(www\.)?youtube\.com\/watch\?v=([a-z0-9\-_]+)(&(t=\d+))?)|((https:\/\/)?youtu\.be\/([a-z0-9\-_]+)(\?(t=\d+))?)\b/i', $contents, $matches);

if( empty($matches) ) return;

# Replacement
foreach($matches[0] as $index => $match)
    $contents = str_replace($match, "<p class='youtube_container'><iframe class='youtube_video' 
    src='https://www.youtube.com/embed/{$matches[4][$index]}?{$matches[6][$index]}' 
    frameborder='0' allowfullscreen></iframe></p>", $contents);

$config->globals["processing_contents"] = $contents;
