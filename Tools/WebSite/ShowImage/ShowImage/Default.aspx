<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="ShowImage._Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>This is the FontPage</title>
</head>
<body>
    <h1>Just Test The Image Shwo</h1>
    <form id="form1" runat="server">
    <div>
    
        <asp:Image ID="Image1" runat="server" ImageUrl="~/images/holidaytext.gif" />
        <br />
        <asp:Image ID="Image2" runat="server" Height="163px" 
            ImageUrl="~/images/holiday08_1.gif" Width="296px" />
        <br />
        <asp:Image ID="Image3" runat="server" Height="159px" 
            ImageUrl="~/images/holiday08_2.gif" Width="297px" />
        <br />
        <asp:Image ID="Image4" runat="server" Height="158px" 
            ImageUrl="~/images/holiday08_3.gif" Width="297px" />
    
        <br />
        <asp:Image ID="Image5" runat="server" ImageUrl="~/images/holidaytext.jpg" />
    
    </div>
    </form>
</body>
</html>
