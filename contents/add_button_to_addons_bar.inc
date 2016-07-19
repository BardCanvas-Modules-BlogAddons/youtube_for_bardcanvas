<?php
/**
 * Addition of button definition for the post editor
 *
 * @package    BardCanvas
 * @subpackage youtube_for_bardcanvas
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

/** @var \SimpleXMLElement $node */
$node = $modules["posts"]->language->form->post_addons->addChild("addon");
$node->addAttribute("function", $this_module->language->addon["function"]);
$node->addAttribute("icon", $this_module->language->addon["icon"]);
$node->addChild("caption", $this_module->language->addon->caption);
$node->addChild("title", $this_module->language->addon->title);
