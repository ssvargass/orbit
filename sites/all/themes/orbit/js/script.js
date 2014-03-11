(function ($) {
  $(document).ready(function(){
    $('#og-wall-form .ob_text').addClass('active');
    $('.views-exposed-form .views-widget-filter-combine').hide_label();
    $('.ob-profile a').click(function(e){
      $('#block-ob-wall-ob-profile').animate({height:'18.5em'},500)
      e.preventDefault();
      return false;
    })
    $('.ob-close').click(function(){
      $('#block-ob-wall-ob-profile').animate({height:'0'},500)
    })
      var output = '<div class="s_event_create">Crear Evento</div>';
      $('#block-afb-1').before(output);
      $('.s_event_create').click(function(){
        if($(this).hasClass('active')){
          $(this).removeClass('active');
          $('#block-afb-1').animate({height: 0},500).removeClass('active');
        } else {
          $(this).addClass('active');
          $('#block-afb-1').addClass('active')
          $('#block-afb-1').animate({height: 730},500, function(){
            $(this).css('height','auto');
          })
        }
      })
  })
  $.fn.hide_label = function(){
    var complete_input = this;
    if($(complete_input).find('input').length > 0){
      if($(complete_input).find('input').val() != ''){
        $(this).find('label').hide();
      }

      $(complete_input).find('input').focus(function() {
        complete_input.find("label").hide();
      });

      $(complete_input).find('input').blur(function() {
        console.log(this);
        if($(this).val() === ''){
          complete_input.find("label").show();
        }
      });
    }
    if($(complete_input).find('textarea').length > 0){
      if($(complete_input).find('textarea').val() != ''){
        $(this).find('label').hide();
      }

      $(complete_input).find('textarea').focus(function() {
        complete_input.find("label").hide();
      });

      $(complete_input).find('textarea').blur(function() {
        console.log(this);
        if($(this).val() === ''){
          complete_input.find("label").show();
        }
      });
    }
  }
	Drupal.behaviors.orbit = {
    attach: function (context, settings) {
      $('#og-wall-form').once('wall_form',function(){
        var form = $(this);
        $('label').click(function(){
          $('.active', form).removeClass('active');
          $(this).parents('.s_add_file').addClass('active');
        })
      });
      
      $('.field-name-ds-user-picture a', context).once('init-colorbox-node-processed', function () {
          var url = $(this).attr('href');
          url = url + '?width=600&height=400';
          $(this).attr('href', url);
          $(this).colorboxNode({'launch': false});
      });
    }
  };
})(jQuery);