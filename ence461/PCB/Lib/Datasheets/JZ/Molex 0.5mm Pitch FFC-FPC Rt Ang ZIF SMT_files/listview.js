window.onload = function(){
	var $dd = "";
	if(document.getElementById("faq-parent") != null 
				&& document.getElementById("faq-parent") != undefined
				&& document.getElementById("faq-parent") != 'undefined')
	{
		var faqParent = document.getElementById("faq-parent");
		var dt = faqParent.getElementsByTagName("dt");
		for(var i=0; i<dt.length; i++){
			dt[i].getElementsByTagName("a")[0].onclick = function(){
				var dd = this.parentNode.nextSibling;
				if(dd.style.display == "" || dd.style.display == "none"){
					if($dd != ""){
						$dd.style.display = "none";
						
					}
					dd.style.display = "block";
					$dd = dd;
							
				}else{
					dd.style.display = "none";
				
				}
								
			}
			
		}
	}
	
}

function $2(id) {
	return document.getElementById(id);
}
function display(id,val) {
	$2(id).style.display=val;
}

var curr_subNav_link = '';
var curr_subNav_popup = '';
function toggleSubNav(num, partCount, noCategory) {
	var refine_link = 'refine_link_'+num;
	var subNav_link = 'subNav_link_'+num;
	var subNav_popup = 'subNav_popup_'+num;
	var normalTopPos = (29.8 * num) + 199;
	if(noCategory)
		normalTopPos = (29.8 * (num-1)) + 199;
	var popupHeight = 255;
	var rowCount = 0;
	if(partCount > 10)
		rowCount = Math.ceil(partCount / 3);
	else
		rowCount = Math.ceil(partCount / 2);
	if(partCount <= 30)
	{
		if(rowCount < 2)
			rowCount = 2;
		popupHeight = 28 * rowCount;
	}
	$2(refine_link).style.height = popupHeight + 'px';
	var windowHeight = getWindowSize();
	var scrollYOffset = getScrollY();
	var normalBottomPos = normalTopPos + popupHeight + 63;
	var diff = (windowHeight + scrollYOffset) - normalBottomPos;
	if (curr_subNav_link != '') {
		display(curr_subNav_popup,'none');
		$2(curr_subNav_link).className='';
	}
	
	if (subNav_link != curr_subNav_link) 
	{
		display(subNav_popup,'block');
		//box small enough that doesn't go off the bottom
		if(diff > 0)
		{
			$2(subNav_popup).style.top = normalTopPos + 'px';
		}
		//box goes off the bottom if its position is same as button
		else
		{
			topPos = normalTopPos - Math.abs(diff);
			//top of box doesn't go off of viewable page, set it to top of box
			if(topPos > scrollYOffset)
			{
				$2(subNav_popup).style.top = (topPos-5) + 'px';
			}
			//if it does, set top of box to the topmost viewable area
			else
			{
				$2(subNav_popup).style.top = scrollYOffset + 'px';
			}
		}
		if(partCount > 10)
		{
			$2(subNav_popup).style.width = '700px';
		}
		else
		{
			$2(subNav_popup).style.width = '445px';
		}
		$2(subNav_link).className='focus';
	
		curr_subNav_link = subNav_link;
		curr_subNav_popup = subNav_popup;
	} else {
	
		curr_subNav_link = '';
		curr_subNav_popup = '';
	
	}
}

function closeSubNav(num) {
	display('subNav_popup_'+num,'none');
	$2(curr_subNav_link).className='';
	curr_subNav_link = '';
	curr_subNav_popup = '';
}


var curr_detail="all";
var details = ['0','1','2','3','4','5','6','7','8','9','10'];
var num_details = details.length;

function show_detail(detail) {
	if (detail != curr_detail) {
		for (var i=0;i<num_details;i++) {
			if(document.getElementById(details[i]) != null 
				&& document.getElementById(details[i]) != undefined
				&& document.getElementById(details[i]) != 'undefined')
				$2(details[i]).style.display='none';
		}
		if (detail == 'all') {
			for (var ii=0;ii<num_details;ii++) {
				if(document.getElementById(details[ii]) != null 
					&& document.getElementById(details[ii]) != undefined
					&& document.getElementById(details[ii]) != 'undefined')
					$2(details[ii]).style.display='block';
			}
		} else {
			$2(detail).style.display='block';
		}
		
		if (detail != 'all') {
		$2(detail + '_link').style.backgroundColor='#525d60';
		$2(detail + '_link').style.color='#fff';
		}
		
		if (curr_detail != 'all') {
		$2(curr_detail + '_link').style.backgroundColor='#fff';
		$2(curr_detail + '_link').style.color='#525d60';
		}
		
		curr_detail = detail;
	}
}

var curr_rel_prod="all";
var rel_prods = ['mateswith','usewith','apptool'];
var num_rel_prods = rel_prods.length;

function show_rel_prods(prod) {
	if (prod != curr_rel_prod) {
		for (var i=0;i<num_rel_prods;i++) {
			if(document.getElementById(rel_prods[i]) != null 
				&& document.getElementById(rel_prods[i]) != undefined
				&& document.getElementById(rel_prods[i]) != 'undefined')
				$2(rel_prods[i]).style.display='none';
		}
		if (prod == 'all_rel') {
			for (var ii=0;ii<num_rel_prods;ii++) {
				if(document.getElementById(rel_prods[ii]) != null 
					&& document.getElementById(rel_prods[ii]) != undefined
					&& document.getElementById(rel_prods[ii]) != 'undefined')
				$2(rel_prods[ii]).style.display='block';
			}
		} else {
			$2(prod).style.display='block';
		}
		if (prod != 'all_rel') {
			$2(prod + '_link').style.backgroundColor='#525d60';
			$2(prod + '_link').style.color='#fff';
		}
		if (curr_rel_prod != 'all_rel') {
			if(document.getElementById(curr_rel_prod + '_link') != null 
				&& document.getElementById(curr_rel_prod + '_link') != undefined
				&& document.getElementById(curr_rel_prod + '_link') != 'undefined')
			{
				$2(curr_rel_prod + '_link').style.backgroundColor='#fff';
				$2(curr_rel_prod + '_link').style.color='#525d60';
			}
		}
		curr_rel_prod = prod;
	}
}

function display(id,type) {
	if (id == 'all') {
		for (var i=1;i<9;i++) {
			$2('prod_cat_'+i).style.display=type;
		}
	} else {
		$2(id).style.display=type;
	}
}

var curr_toggle = 'all';
function toggle(id) {
	if (curr_toggle != id) {
		display(curr_toggle,'none');
		display(id,'block');
		highlight_tab(id);
	}
	curr_toggle = id;
}

function highlight_tab(id) {
	if (id != 'all') {
		$2(id + '_link').style.backgroundColor='#525d60';
		$2(id + '_link').style.color='#fff';
	}
	if (curr_toggle != 'all') {
			$2(curr_toggle).style.backgroundColor='#fff';
			$2(curr_toggle).style.color='#525d60';
		}
}

function tab_over(id) {
	if (curr_toggle != id) {
		$2(id).style.backgroundColor='#525d60';
		$2(id).style.color='#fff';
	}
}

function tab_out(id) {
	if (curr_toggle != id) {
		$2(id).style.backgroundColor='#fff';
		$2(id).style.color='#525d60';
	}
}

function ValidateCompare(form, itemlist, coreQueryString, jsessionid)
{
	var all = itemlist;
	var upper_limit = form.elements.length;
	if(itemlist == "all")
		itemlist = '';
	var itemlist_array = [];
	if(itemlist.length > 0)
		itemlist_array = itemlist.split(",");
	var CompareQty = itemlist_array.length;
	var strAlertMessage = "You must select at least two, but no more than 10 products to compare.";
	for (var i = 0; i < upper_limit; i++)
	{
		if (form.elements[i].name == "Itemlist")
		{
			itemValue = form.elements[i].value
			if(form.elements[i].checked || all == "all")
			{	
				if(itemlist.indexOf(itemValue) < 0)
				{	
					CompareQty++;
					if(itemlist.length > 0)
						itemlist += ",";
					itemlist += form.elements[i].value;
				}
			}
			else
			{
				if(itemlist.indexOf(itemValue) > -1)
				{	
					itemlist = itemlist.replace(itemValue, "");
					itemlist = itemlist.replace(",,", ",");
					CompareQty--;
				}
			}
		}
	}
	if (CompareQty < 2 || CompareQty > 10)
	{
		//sometimes we have extra commas that adds to the count
		for(var i = 0; i < itemlist_array.length && CompareQty > 10; i++)
		{
			if(itemlist_array[i].length == 0)
				CompareQty--;
		}
		if (CompareQty < 2 || CompareQty > 10)
			alert(strAlertMessage);
	}
	else
	{
		window.location = "compare.jsp"+jsessionid+"?" + coreQueryString + "&Itemlist=" + itemlist; 
	}
	return;
}

function ClearItems(form){
	count = form.elements.length;
    	for (i=0; i < count; i++) 
    	{
		if(form.elements[i].checked)
	    	{
	    		form.elements[i].checked = 0; 
	    	}
	}
}

function switchPage(form, itemlist, queryString, path, jsessionid)
{
	var uppper_limit
	var itemlist_array = itemlist.split(",");
	var CompareQty = itemlist_array.length;
	
	upper_limit = form.elements.length;
	var strAlertMessage = "You selected more than the maximum of eight products for comparison";
		for (var i = 0; i < upper_limit; i++)
	{
		if (form.elements[i].name == "Itemlist")
		{
			itemValue = form.elements[i].value
			if(form.elements[i].checked)
			{	
				if(itemlist.indexOf(itemValue) < 0)
				{	
					CompareQty++;
					if(itemlist.length > 0)
						itemlist += ",";
					itemlist += form.elements[i].value;
				}
			}
			else
			{
				if(itemlist.indexOf(itemValue) > -1)
				{	
					itemlist = itemlist.replace(itemValue, "");
					itemlist = itemlist.replace(",,", ",");
					CompareQty--;
				}
			}
		}
	}
	if (CompareQty > 10)
	{
		//sometimes we have extra commas that adds to the count
		for(var i = 0; i < itemlist_array.length && CompareQty > 10; i++)
		{
			if(itemlist_array[i].length == 0)
				CompareQty--;
		}
		if (CompareQty > 10)
			alert(strAlertMessage);
	}
	else
	{
		window.location = "listview.jsp"+jsessionid+"?" + queryString + escape(path) + "&Itemlist=" + itemlist; 
	}
}

function switchNumPerPage(form, itemlist, queryString, path, numPerPage, jsessionid)
{
	var upper_limit = 0;
	var itemlist_array = itemlist.split(",");
	var CompareQty = itemlist_array.length;
	
	if(form != null)
		upper_limit = form.elements.length;
	var strAlertMessage = "You selected more than the maximum of eight products for comparison";
		for (var i = 0; i < upper_limit; i++)
	{
		if (form.elements[i].name == "Itemlist")
		{
			itemValue = form.elements[i].value
			if(form.elements[i].checked)
			{	
				if(itemlist.indexOf(itemValue) < 0)
				{	
					CompareQty++;
					if(itemlist.length > 0)
						itemlist += ",";
					itemlist += form.elements[i].value;
				}
			}
			else
			{
				if(itemlist.indexOf(itemValue) > -1)
				{	
					itemlist = itemlist.replace(itemValue, "");
					itemlist = itemlist.replace(",,", ",");
					CompareQty--;
				}
			}
		}
	}
	if (CompareQty > 10)
	{
		//sometimes we have extra commas that adds to the count
		for(var i = 0; i < itemlist_array.length && CompareQty > 10; i++)
		{
			if(itemlist_array[i].length == 0)
				CompareQty--;
		}
		if (CompareQty > 10)
			alert(strAlertMessage);
	}
	else
	{
		window.location = "listview.jsp"+jsessionid+"?" + queryString + escape(path) + "&npp=" + numPerPage + "&Itemlist=" + itemlist; 
	}
}


function switchNumPerPageCrawl(form, queryString, numPerPage, jsessionid)
{
	window.location = "crawllistview.jsp" + jsessionid + "?" + queryString + "&npp=" + numPerPage; 
}




function getWindowSize() {
  var myWidth = 0, myHeight = 0;
  if( typeof( window.innerWidth ) == 'number' ) {
    //Non-IE
    myWidth = window.innerWidth;
    myHeight = window.innerHeight;
  } else if( document.documentElement && ( document.documentElement.clientWidth || document.documentElement.clientHeight ) ) {
    //IE 6+ in 'standards compliant mode'
    myWidth = document.documentElement.clientWidth;
    myHeight = document.documentElement.clientHeight;
  } else if( document.body && ( document.body.clientWidth || document.body.clientHeight ) ) {
    //IE 4 compatible
    myWidth = document.body.clientWidth;
    myHeight = document.body.clientHeight;
  }
  //window.alert( 'Width = ' + myWidth );
  //window.alert( 'Height = ' + myHeight );
  return myHeight;
}

function getScrollY() {
  var scrOfX = 0, scrOfY = 0;
  if( typeof( window.pageYOffset ) == 'number' ) {
    //Netscape compliant
    scrOfY = window.pageYOffset;
    scrOfX = window.pageXOffset;
  } else if( document.body && ( document.body.scrollLeft || document.body.scrollTop ) ) {
    //DOM compliant
    scrOfY = document.body.scrollTop;
    scrOfX = document.body.scrollLeft;
  } else if( document.documentElement && ( document.documentElement.scrollLeft || document.documentElement.scrollTop ) ) {
    //IE6 standards compliant mode
    scrOfY = document.documentElement.scrollTop;
    scrOfX = document.documentElement.scrollLeft;
  }
  return scrOfY;
}

function openNewWindow(path) {
	window.open(path, "newWindow", "left=100,top=100,width=300,height=300,toolbar=0,resizable=1,scrollbars=1");
}

function inputText(cmd, defaultValue) {
	var i = document.getElementById('search_phrase');
	switch (cmd) {
	case 'on' :
		if (i.value == defaultValue) { i.value = ''; }
		break;
	case 'off' :
		if (i.value == '') { i.value = defaultValue; }
		break;
	}
}