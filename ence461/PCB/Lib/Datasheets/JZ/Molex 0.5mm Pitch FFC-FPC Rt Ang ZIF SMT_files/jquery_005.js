$(document).ready(function(){
	
	$('.showandhide').show();
	
	$('a.popup').fancybox({padding: 0, showCloseButton:false, hideOnOverlayClick:false });
	$('a.popup2').each(function() {
		$(this).click(function() {
			thisindex = $(this).parent().parent().children().index($(this).parent());
		});
		$(this).fancybox({padding: 0, showCloseButton:true, onComplete: 	function () {
			$('#fancybox-close').text('close [x]');
			$('.close').click(function() { $.fancybox.close(); });
			$('.accordion').accordion({ 'active': thisindex, 'autoHeight' : false, 'collapsible': true });
		} });
	});
	
	$('input.popup').parents('form').submit(function() {    
    	var url = $(this).attr('action') + '?' + $(this).formSerialize(); 
    	$('<a href="'+url+'" />').fancybox({padding: 0, showCloseButton:false }).trigger('click');
    	return false; 
    });
	
	// Datepicker
    $('input.date').datepicker({
        dateFormat: 'mm/dd/yy',
		changeMonth: true
    });

    $('#completiondate').datepicker({
        dateFormat: 'mm/dd/yy',
		minDate: '+0d'
    });

	var dates = $( "#fromdate, #todate" ).datepicker({
        beforeShow: customRange,
        firstDay: 1, 
        changeFirstDay: false,
        dateFormat: 'mm/dd/yy',
		changeMonth: true,
		numberOfMonths: 1
	});
    
	function customRange(input) { 
	    var min = new Date(2008, 11 - 1, 1), //Set this to your absolute minimum date
	        dateMin = min,
	        dateMax = null,
	        dayRange = 90; // Set this to the range of days you want to restrict to

	    if (input.id === "fromdate") {
	        if ($("#todate").datepicker("getDate") != null) {
	            dateMax = $("#todate").datepicker("getDate");
	            dateMin = $("#todate").datepicker("getDate");
	            dateMin.setDate(dateMin.getDate() - dayRange);
	            if (dateMin < min) {
	                dateMin = min;
	            }
	        }
	        else {
	            dateMax = new Date; //Set this to your absolute maximum date
	        }                      
	    }
	    else if (input.id === "todate") {
	        dateMax = new Date; //Set this to your absolute maximum date
	        if ($("#fromdate").datepicker("getDate") != null) {
	            dateMin = $("#fromdate").datepicker("getDate");
	            var rangeMax = new Date(dateMin.getFullYear(), dateMin.getMonth(),dateMin.getDate() + dayRange);

	            if(rangeMax < dateMax) {
	                dateMax = rangeMax; 
	            }
	        }
	    }
	    return {
	        minDate: dateMin, 
	        maxDate: dateMax
	    };     
	}

	
	$('.zebra tr:nth-child(2n) td, .zebra tr:nth-child(2n) th, .zebra tbody tr:nth-child(2n)').addClass('even');
	
	$("input[placeholder]").placeHeld();
	
    $('.tabs-nav li:last-child').addClass('last');
    var $tabs2 =   $('.noshowalltabs').tabs();
    $('.results_tabs_wrapper').tabs({selected: 0});
    
    // Preselect tab
    if($('.noshowalltabs .selectedtab').length > 0) {
		$tabs2.tabs('select', $('.sfContent').index($('.selectedtab')));
	}
    
    // Show all link    
    $('.show_all').bind('click',function(e) {
    	var current_tabs = $(this).attr('title');
    	$('#'+current_tabs).find('.ui-tabs-selected ').removeClass('.ui-tabs-selected');
    	$('#'+current_tabs).tabs( "destroy" );
    	e.preventDefault();
    });
    
    // Stop showing all    
    $('.tabbed, .tabs').find('li').find('a').bind('click', function(e) {
    	var selected_tab = parseInt($(this).attr('id').replace(/[^-\d\.]/g, '')) - 1;
    	$(this).parents('.tabbed, .tabs').tabs({selected: selected_tab});
    	e.preventDefault();
    });
    
    // Back link
    $('.back').bind('click', function(e) {
    	$(this).parents('.results_tabs_wrapper').tabs({selected: 0});
    	e.preventDefault();
    });
    
    // Search center
    $('.search').find('.clearfix').each(function(){
        var width = 0;
        $(this).children().each(function(){
            width += $(this).width();
        });
        $(this).width(width + 30);
    });
    
    // Navigation
    $('#nav li').each(function(){
        $(this).children('ul').hide();

        if ($(this).find('> ul')[0]) {
            $(this).children('a').addClass('arrow').append('<span class="image" />');
        }
        
        $(this).hover(function(){
            $(this).addClass('hover');
            $(this).children('ul').stop(true, true).show(250);
        }, function(){
            $(this).removeClass('hover');
            $(this).children('ul').stop(true, true).hide();
        });
        
    });
    
    // Flyout menu
    
    $('#featurenav ul li a:not(.refine_col li a)').bind('click',function(e) {
    	$('.subNav_popup').hide();
    	$(this).next().toggle();
    	e.preventDefault();
    });
    
    function closeSubNav(navid) {
    	$('#subNav_popup_'+navid).hide();
    	$(this).preventDefault();
    }

    // First and last classes
    $('#nav > li:first').addClass('first');
    $('#nav > li:last').addClass('last');
    
    // Vertically align
    (function ($) {
        $.fn.vAlign = function() {
            return this.each(function(i){
                var ah = $(this).height();
                var ph = $(this).parent().height();
                var mh = (ph - ah) / 2;
                $(this).css('padding-top', mh + 'px');
            });
        };
    })(jQuery);
    
    // Vertically align
    $('#site-nav > li a').wrapInner('<span class="text" />');
    $('#site-nav > li a span').vAlign();

    // Footer
    $('#footer').find('.links').each(function(){
        var width = 0;
        $(this).children().each(function(){
            width += $(this).width();
        });
        $(this).width(width + 10);
    });
    // news scroller on homepage
    $('#product-scroll h2').after('<a class="nav prev" id="prod-prev" href="#">Previous</a><a class="nav next" id="prod-next" href="#">Next</a>');
    $('#inno-products').cycle({ 
        fx: 'scrollHorz', 
        cleartype:  1, // enable cleartype corrections 				
        speed: 500, 
        timeout:0,
        next:'#prod-next',
        prev:'#prod-prev',
        pause:1
        });

    // news scroller on homepage
    $('#industry-scroll h2').after('<a class="nav prev" id="ind-prev" href="#">Previous</a><a class="nav next" id="ind-next" href="#">Next</a>');
    $('#industries').cycle({ 
        fx: 'scrollHorz', 
        cleartype:  1, // enable cleartype corrections 				
        speed: 500, 
        timeout:0,
        next:'#ind-next',
        prev:'#ind-prev',
        random: 1,
        pause:1
        });
    
    
	$('.cycle').cycle({
        pager: '.cycle-nav'
    });
    $('.pause').click(function(e) {
        if ($(this).children('span').hasClass('playing')) {
            $(this).children('span').removeClass('playing').addClass('paused');
            $(this).children('span').parent().siblings('.cycle').cycle('pause');
            e.preventDefault();
        } else {
            $(this).children('span').removeClass('paused').addClass('playing');
            $(this).children('span').parent().siblings('.cycle').cycle('resume');
            e.preventDefault();
        }
    });

	$('.slideshow').cycle({				
		fx: 'fade',
		timeout: 8000,
		speed: 2000		
	});
    
  
    //$('#site-nav ul ul').each(function(){
    //    $(this).find('li:eq(0)').css('padding-top', '7px');    
    //});
    
    $("#site-nav ul ul ul").parent().find("a:eq(0)").addClass('parent'); //Only shows drop down trigger when js is enabled - Adds empty span tag after ul.subnav


    $('#primary-nav > li').hover(function() {
        $('.top-nav', this).addClass('active');
    },
    function() {
        $('.top-nav', this).removeClass('active');
    });

    $('#site-nav li').hover(function() {
        $(this).find('ul:eq(0)').show();    
    },
    function() {
        $(this).find('ul:eq(0)').hide();
    });
    
   $('#site-nav ul ul li:last-child > a').css({'border-bottom' : '0 none', 'padding-bottom' : '5px'});
   
//     $('.default-text').each(function() {
//         var default_value = this.value;
//         $(this).focus(function() {
//             if(this.value == default_value) {
//                 this.value = '';
//             }
//         });
//         $(this).blur(function() {
//             if(this.value == '') {
//                 this.value = default_value;
//             }
//         });
//     });
    
    /* family */
    
    $('.overview').click(function(e) {
        $tabs2.tabs('select', 0);
	});
	$('.features').click(function(e) {
		$tabs2.tabs('select', 1);
	});
	$('.applications').click(function(e) {
		$tabs2.tabs('select', 2);
	});
	$('.tabs table tr:even td').addClass('even');
	
	$('.accordion .scroll').jScrollPane({
		scrollbarWidth: 6,
		scrollbarMargin: 10,
		showArrows: true
	});       
    $('.accordion').accordion({ animated: false, autoHeight: false });
    $('.accordion h2').append('<span/>');
    
    /* Video page */
    
    $('.learnmore').bind('click',function(e) {
    	$(this).next('div').toggle();
    	e.preventDefault();
    });
    
    $('.rel-video a').bind('click',function(e) {
    	$('.mainvideo iframe').attr('src',$(this).attr('href'));
    	$('.video-info').text($(this).next('.synopsis').text());
    	e.preventDefault();
    });
    
    $('iframe').each(function() {
		var url = $(this).attr("src");
		$(this).attr("src",url+"?wmode=transparent");
	});
    
    /* New part landing */
    
    $('.accordion_show_all').click(function(e) {
    	if(!$('.accordion').hasClass('ui-accordion-disabled')) {
			$('.accordion').accordion('disable');
			$('.accordion .content').show();
			$('.accordion h3 span').removeClass('ui-icon-triangle-1-e').addClass('ui-icon-triangle-1-s');
			$(this).text('Collapse all');
    	} else {
			$('.accordion').accordion('enable');
			$('.accordion .content').hide();
			$('.accordion h3 span').removeClass('ui-icon-triangle-1-s').addClass('ui-icon-triangle-1-e');    	
			$(this).text('View all');
    	}
		e.preventDefault();
    });	
	
	$('#datasheet_show_all').trigger('click'); // Show all by default on datasheet
	
	$('input[required]:not(.noasterisk), select[required]:not(.noasterisk), textarea[required]:not(.noasterisk), input.required:not(.noasterisk), select.required:not(.noasterisk), textarea.required:not(.noasterisk)').prev('label').append(' <span class="required">*</span>');
	$('input[required]:not(.noasterisk), select[required]:not(.noasterisk), textarea[required]:not(.noasterisk), input.required:not(.noasterisk), select.required:not(.noasterisk), textarea.required:not(.noasterisk)').parent().prev('label').append(' <span class="required">*</span>');

	if($('.formvalidate').length > 0) {
		$('.formvalidate').validate();	
	}
	
	/* CER specific */
	
	$('.hastextfield').change(function() {
		if($(this).is(':checked')) {
			$(this).next().next('input').removeAttr('disabled');
		} else {
			$(this).next().next('input').val('').trigger('blur').attr('disabled','disabled');
		}
	});
	
	$('.CERsearchform').submit(function(e) {
	 	$('.searcherror').hide();
	 	$('.CERlanding .errormessage').hide();
		var submitform = false;
		var errormsg = '';
		$('.CERsearchform input.text').each(function() {
			if($(this).val() != '') {
				submitform = true;
			}
		});
	 	if(!submitform) {
	 		$('.searcherror').show();
	 		e.preventDefault();
	  		return false; 		
		}else {
			if($(this).valid()) {
				$('.FormSubmit').val('Searching');
			}
		}		
	});
	
	$('.CERrequest').submit(function(e){
	 	$('.CER .errormessage').hide();
		$("input[placeholder]").trigger('blur');
		var submitform = false;
		var error = false;
	 	$('.checkbox').each(function() {
	 		if($(this).hasClass('hastextfield') && $(this).is(':checked') && ($(this).next().next('input').val() == '' || $(this).next().next('input').hasClass('placeheld'))) {
	 			submitform = false;
	 			$('#emptytextfield').show();
				error = true;
	 			hastext = false;
	 			return false;
	 		}
			if($(this).is(':checked')) {
				submitform = true;
			}
	 	});
	 	if(!submitform) {
	 		if(!error) {
				$('#notchecked').show();
	 		}
	 		e.preventDefault();
	  		return false; 
	  	} else {
			if($(this).valid()) {
				$('.FormSubmit').val('Processing').attr('disabled','disabled');
			}
		}
	});
    

	$('.showandhide').hide();
	
});