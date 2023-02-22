/*
This code is embedded (via SCRIPT SRC="" tag)
into editorial and family HTMLs and will process
all links that want to point to BVSN material.

Written by: Saurab Bhargava
Date: 03/27/01
*/

if (parent.sideNav != null)
{
     document.domain = "molex.com";
}

function buildLink(oid, type) {
	//Variables
	if (parent.frameless == "yes")
	{
		buildLinkFrameless(oid, type, null, null);
		return; 
	}
	
	var scrName 		= (parent.sideNav == null? window.opener.scrName : parent.sideNav.scrName); //from side nav
	var familyPage 		= scrName + "/family/intro.jsp?";
	var superFamilyPage = scrName + "/super_family/super_family.jsp?"
    var searchPage      = parent.scrName + "/products/listview.jsp?channel=Products";
	var productsPage    = parent.scrName + "/products/products.jsp?channel=Products";
	if(type == null) //Set type to family as default
	{
		type = 'F';
	}

	switch (type) //Determines where link should go
	{
		case("F"): //Family
			sNav = "&channel=Products&chanName=family&familyOID=" + oid + "&frellink=Introduction";
			mCnt = familyPage + "oid=" + oid + sNav + "&pageTitle=Introduction";
			break;
		case("SF"): //Super Family
			sNav = "channel=Products&chanName=superFamily&superFamOID=" + oid;
			mCnt = superFamilyPage + "&oid=" + oid + sNav + "&pageTitle=Overview";
			break;
		case("SRSD"): //Series Part Detail
		    mCnt = searchPage + "&sType=p&query=" + oid;
			break;
		case("SRSS"): //Series Datasheet
		    mCnt = searchPage + "&sType=s&query=" + oid;
			break;
		default: //Send to home page
			mCnt = productsPage;
			break;
	} //end switch(type)

  if (parent.sideNav != null)
  {
	     parent.location = mCnt;
  }
  else
  {
  	   window.opener.location = mCnt;
  	   window.close();
  }
} 
//End function buildLink(type, oid)

function buildLinkFrameless(oid, type, jsessionid, cgiPath) {
	if(cgiPath == null)
		cgiPath = parent.scrName;
	if(jsessionid == null)
	{
		if(jsessionID == null)
			jsessionid = '';
		else
			jsessionid = jsessionID;
	}
	var familyPage 		= cgiPath + "/products/productRedirect.jsp" + jsessionid + "?oid=" + oid + "&type=" + type;
	var searchPage      = cgiPath + "/products/listview.jsp" + jsessionid + "?channel=Products";
	var productsPage    = cgiPath + "/products/products.jsp" + jsessionid + "?channel=Products";
	
	if(type == null) //Set type to family as default
	{
		type = 'F';
	}

	switch (type) //Determines where link should go
	{
		case("F"): //Family
			mCnt = familyPage;
			break;
		case("SF"): //Super Family
			mCnt = familyPage;
			break;
		case("SRSD"): //Series Part Detail
			mCnt = searchPage + "&sType=p&query=" + oid;
			break;
		case("SRSS"): //Series Datasheet
			mCnt = searchPage + "&sType=s&query=" + oid;
			break;
		default: //Send to home page
			mCnt = productsPage;
			break;
	} //end switch(type)
	window.location = mCnt;
} 

//End function buildLink(type, oid)
function queryFilter(queryString, appendQueryString)
{
	queryString = queryString + "&" + appendQueryString;
 	var pairs    = queryString.split("&");
    var strQuery = "";
    var included = "";
    for (var i=pairs.length-1; i > -1; i--) 
    { 
         var pos = pairs[i].indexOf('='); 
         if (pos >= 0) 
         {  
              var argname = pairs[i].substring(0,pos); 
              var value   = pairs[i].substring(pos+1); 
              if (included.indexOf("&" + argname + "&") < 0 )
              { 
      			   included = included + "&" + argname + "&";
                   strQuery = strQuery + argname + "=" + value + "&";
              }
         } 
    }
    if(strQuery.charAt(strQuery.length-1) == '&')
    	strQuery = strQuery.substring(0, strQuery.length-1);
    
    return strQuery;
}

function loadURL(page, qstring, pos)
{	    
	page = page.replace(/\/cgi-bin\/bv\/molex\/jsp/, "/molex");
     var position = "";
     if (pos != null && pos != "")
     {
          position = "#" + pos;
     }
     var query    = window.location.search.substring(1); 
     var strQuery = queryFilter(query, qstring);
     var url  = page + '?' + strQuery + position;
     parent.location = url;
}

function buildFamily(key, jsessionid, cgiPath, ftype) 
{
	if(cgiPath == null)
		cgiPath = parent.scrName;
	if(jsessionid == null)
	{
		if(jsessionID == null)
			jsessionid = '';
		else
			jsessionid = jsessionID;
	}

	if (!window.langPref)
	{
		langPref = "english";
	}
	var productsPage = "";
	if(ftype == 'F')
	{
		productsPage    = cgiPath + "/products/family" + jsessionid + "?key="+key+"&channel=products&chanName=family&pageTitle=Introduction";
	}
	else
	{
		productsPage    = cgiPath + "/products/group" + jsessionid + "?key="+key + "&channel=PRODUCTS";
	}

	mCnt = productsPage;
	window.location = mCnt;
}

function buildSelectedFamily(key, jsessionid, cgiPath, selected, ftype) 
{
	if(cgiPath == null)
		cgiPath = parent.scrName;
	if(jsessionid == null)
	{
		if(jsessionID == null)
			jsessionid = '';
		else
			jsessionid = jsessionID;
	}
	if (!window.langPref)
	{
		langPref = "english";
	}
	var productsPage = "";
	if(ftype == 'F')
	{
		productsPage    = cgiPath + "/products/family" + jsessionid + "?key="+key+"&channel=products&chanName=family&pageTitle=Introduction&selectedKey=" + selected;
	}
	else
	{
		productsPage    = cgiPath + "/products/group" + jsessionid + "?key="+key + "&channel=PRODUCTS&selectedKey=" + selected;
	}
	mCnt = productsPage;
	window.location = mCnt;
} 

function loadConfigURL(kbsName)
{
  var strQuery = parent.location.search.substring(1);
  var aryURLParams = strQuery.split("&");
  strSuperFamOID = ""
  strFamilyOID   = "" 
  strMCnt        = "" 

	for (var intI = 0; intI < aryURLParams.length; intI++)
  {
		strURLParam = aryURLParams[intI].toLowerCase()

		if (strURLParam.substring(0,11) == "superfamoid")
		{
			arySuperFamOID = aryURLParams[intI].split("=");
			strSuperFamOID = arySuperFamOID[1];
		}
		else if (strURLParam.substring(0,9) == "familyoid")
		{
			aryFamilyOID = aryURLParams[intI].split("=");
			strFamilyOID = aryFamilyOID[1];
		}
	}
  var url = parent.scrName + "/user/validation?jsession="+sId+"&kbsName=" + kbsName + "&superFamOID=" + strSuperFamOID + "&familyOID=" + strFamilyOID + "&pageTitle=Introduction&channel=Products&chanName=family&frellink=Introduction";
  var w = window.open(url, 'project', 'width='+screen.width*.98+',height='+screen.height*.85+',top=0,left=5,toolbar=yes,addressbar=no,titlebar=no,location=no,resizable=yes,scrollbars=yes'); 
}