
tinymce.PluginManager.add('youtube_for_bardcanvas', function(ed, url)
{
    var $strings = $('#youtube_for_bardcanvas_tinymce_strings');
    var _title    = $strings.find('.title').text();
    var _caption  = $strings.find('.caption').text();
    var _invalid  = $strings.find('.invalid_link').text();
    
    ed.addCommand('youtube_for_bardcanvas', function()
    {
        var link = prompt(_caption, '');
        
        if( link == null ) return;
        
        if( link.match(/^((https:\/\/)?(www\.)?youtube\.com\/watch\?v=.*)|((https:\/\/)?youtu\.be\/.*)/i) == null )
        {
            alert( _invalid );
            return;
        }
        
        if( link.match(/^https:\/\//i) == null ) link = 'https://' + link;
        
        ed.insertContent(
            '<a class="youtube_link" href="' + link + '">' + link + '</a>'
        );
    });
    
    // Register example button
    ed.addButton('youtube_for_bardcanvas', {
        title: _title,
        cmd:   'youtube_for_bardcanvas',
        image: $_FULL_ROOT_PATH + '/youtube_for_bardcanvas/media/editor_icon.png'
    });
});
