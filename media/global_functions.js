/**
 * Global functions for the module
 *
 * @package    HNG2
 * @subpackage youtube_for_editor
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

// Styles to add to tinymce
tinymce_default_css_files[tinymce_default_css_files.length]
    = $_FULL_ROOT_PATH + '/youtube_for_editor/media/global_styles~v' + $_SCRIPTS_VERSION + '.css';

// Buttons collection below the post editor
if( typeof $_POST_ADDON_FUNCTIONS == 'undefined' )
    var $_POST_ADDON_FUNCTIONS = {};

// Callback for the button below the editor
$_POST_ADDON_FUNCTIONS['embed_youtube_link_in_post_editor'] = function($trigger, $form)
{
    var $strings = $('#youtube_for_editor_tinymce_strings');
    var _title    = $strings.find('.title').text();
    var _caption  = $strings.find('.caption').text();
    var _invalid  = $strings.find('.invalid_link').text();
    
    var editor_id = $form.find('textarea.tinymce').attr('id');
    var editor    = tinymce.get(editor_id);
    editor.windowManager.open({
        title: _title,
        body: [
            {type: 'textbox', name: 'yt_link', label: _caption}
        ],
        onsubmit: function(e) {
            var link = e.data.yt_link;
            if( link.match(/^((https:\/\/)?(www\.)?youtube\.com\/watch\?v=.*)|((https:\/\/)?youtu\.be\/.*)/i) == null )
            {
                alert( _invalid );
                return;
            }
            
            if( link.match(/^https:\/\//i) == null ) link = 'https://' + link;
            
            editor.insertContent(
                '<a class="youtube_link" href="' + link + '">' + link + '</a>'
            );
        }
    });
};
