function addItemsToCart(form, listID, itemlist, coreQueryString, jsessionid)
{
	var all = itemlist;
	var upper_limit = form.elements.length;
	if(itemlist == "all")
		itemlist = '';
	var itemlist_array = [];
	if(itemlist.length > 0)
		itemlist_array = itemlist.split(",");
	var CompareQty = itemlist_array.length;
	var strAlertMessage = "You must select at least one part, but not more than 20.";
	for (var i = 0; i < upper_limit; i++)
	{
		if (form.elements[i].name == "Itemlist")
		{
			itemValue = form.elements[i].value
			itemValue = itemValue.replace(/[^0-9]/g,"");
			if(form.elements[i].checked || all == "all")
			{	
				if(itemlist.indexOf(itemValue) < 0)
				{	
					CompareQty++;
					if(itemlist.length > 0)
						itemlist += ",";
					itemlist += itemValue;
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
	if (CompareQty < 1 || CompareQty > 20)
	{
		//sometimes we have extra commas that adds to the count
		for(var i = 0; i < itemlist_array.length && CompareQty > 20; i++)
		{
			if(itemlist_array[i].length == 0)
				CompareQty--;
		}
		if (CompareQty < 1 || CompareQty > 20)
			alert(strAlertMessage);
	}
	else
	{
		if(listID == '')
			addItemsToNewList('partcart.jsp' + jsessionid, itemlist, coreQueryString);
		else
			addItemsToExistingList('partcart.jsp' + jsessionid, listID, itemlist, coreQueryString);
	}
	return;
}

function removeItemsFromCart(cartPage, form, listID, coreQueryString)
{
	var all = itemlist;
	var upper_limit = form.elements.length;
	var CompareQty = 0;
	var itemlist = '';
	var strAlertMessage = "You must select at least one part";
	for (var i = 0; i < upper_limit; i++)
	{
		if (form.elements[i].name == "Itemlist")
		{
			itemValue = form.elements[i].value;
			itemValue = itemValue.replace(/[^0-9]/g,"");
			if(form.elements[i].checked)
			{	
				if(itemlist.indexOf(itemValue) < 0)
				{	
					CompareQty++;
					if(itemlist.length > 0)
						itemlist += ",";
					itemlist += itemValue;
				}
			}
		}
	}
	if (CompareQty < 1 )
	{
		alert(strAlertMessage);
	}
	else
	{
		window.location = cartPage + '?action=update&remove=y&Itemlist=' + itemlist + '&listID='+ listID +'&' + coreQueryString;
	}
	return;
}

function inputItemsToPartCart(cartPage, form, listID, coreQueryString)
{
	var all = itemlist;
	var upper_limit = form.elements.length;
	var CompareQty = 0;
	var itemlist = '';
	var strAlertMessage = "You must input at least one part.";
	for (var i = 0; i < upper_limit; i++)
	{
		if (form.elements[i].name == "Itemlist")
		{
			itemValue = form.elements[i].value
			itemValue = itemValue.replace(/[^0-9]/g,"");
			if(itemlist.indexOf(itemValue) < 0)
			{	
				CompareQty++;
				if(itemlist.length > 0)
					itemlist += ",";
				itemlist += itemValue;
			}
		}
	}
	if (CompareQty < 1)
	{
		alert(strAlertMessage);
	}
	else
	{
		if(listID == '')
			addItemsToNewList(cartPage, itemlist, coreQueryString);
		else
			addItemsToExistingList(cartPage, listID, itemlist, coreQueryString);
	}
	return;
}

function addItemsToNewList(cartPage, itemlist,queryString)
{
	var listNameObj = document.getElementById('listName');
	var listDescObj = document.getElementById('listDesc');
	if(listNameObj.value != '')
	{
		if(itemlist == '')
		{
			window.location = cartPage + '?action=addList&listID=0&listName=' 
				+ listNameObj.value + '&listDesc=' + listDescObj.value + '&' + queryString;
		}
		else
		{
			window.location = cartPage + '?action=update&listID=0&Itemlist='+itemlist+'&listName=' 
				+ listNameObj.value + '&listDesc=' + listDescObj.value + '&' + queryString;
		}
	}
	else 
	{
		alert('List Name cannot be empty');	
	}
}

function addItemsToExistingList(cartPage, listID, itemlist, queryString)
{
	window.location = cartPage + '?action=update&Itemlist=' + itemlist + '&listID='+ listID +'&' + queryString;
}

function editList(cartPage, listID, queryString)
{
	var listNameObj = document.getElementById('listChangeName');
	var listDescObj = document.getElementById('listChangeDesc');
	if(listNameObj.value != '')
	{
		window.location = cartPage + '?action=editList&listID='+ listID +'&listName=' 
				+ listNameObj.value + '&listDesc=' + listDescObj.value + '&' + queryString;
	}
	else 
	{
		alert('List Name cannot be empty');	
	}
}


function updateNote(cartPage, inputName,queryString)
{
	var inputObj = document.getElementById(inputName);
	window.location = cartPage + '?action=updateNote&note=' + inputObj.value + '&' + queryString;
}

function sampleRequest(form, requestURL, num)
{
	var itemCount = 0;
	var itemlist = '';
	var upper_limit = form.elements.length;
	var strAlertMessage = "You must select at least one part, but not more than " + num;
	for (var i = 0; i < upper_limit; i++)
	{
		if (form.elements[i].name == "Itemlist")
		{
			itemValue = form.elements[i].value
			if(form.elements[i].checked)
			{		
				itemCount++;
				itemValue = form.elements[i].value;
				itemValue = itemValue.replace(/[^0-9]/g,"");
				itemlist += "&samplePart=" + itemValue;
			}
		}
	}

	if(itemCount == 0)
	{
		alert("You haven't selected any parts");
	}
	else if(itemCount <= num)
	{		
		window.location = requestURL + itemlist;
	}
	else
	{
		alert(strAlertMessage);
	}
}

function pricingRequest(form, requestURL)
{
	var itemCount = 0;
	var itemlist = '';
	var upper_limit = form.elements.length;
	var strAlertMessage = "You must select at least one part";
	for (var i = 0; i < upper_limit; i++)
	{
		if (form.elements[i].name == "Itemlist")
		{
			itemValue = form.elements[i].value
			if(form.elements[i].checked)
			{		
				itemCount++;
				itemValue = form.elements[i].value;
				itemValue = itemValue.replace(/[^0-9]/g,"");
				itemlist += "&pricePart=" + itemValue;
			}
		}
	}
	if(itemCount == 0)
	{
		alert("You haven't selected any parts");
	}
	else if(itemCount <= 10)
	{		
		window.location = requestURL + itemlist;
	}
	else
	{
		alert(strAlertMessage);
	}
}

function updatePermission(queryString, jsessionid)
{
	var permission = '';
	if (document.permission_form.noRead.checked)
	{
		permission = 'noRead';
	}
	else if (document.permission_form.noWrite.checked)
	{
		permission = 'noWrite';
	}
	window.location = 'partcart.jsp'+jsessionid+'?action=updatePermission&permission='+permission+'&' + queryString;
}

function popUpToggle(id) {
	$('#'+id).toggle();
}

function popUpBottom(id, num) {
	$('#'+id).toggle();
	//topcss =(148.75 * num) + (150 + 29) + (4 * (num - 1)) - (4) + 'px'; //header height: 176px  title: 29px
	topcss =10 + 'px';
	$('#'+id).css('top',topcss);
}

