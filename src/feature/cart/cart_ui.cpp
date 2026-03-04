#include <windows.h>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include "cart_service.h"
#include "cart_ui.h"

//window setup
/*void InitApplication(HINSTANCE hInstance)
{
    WNDCLASSEX wc{};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(150,175,220));
    wc.lpszClassName = L"MainWindow";

    RegisterClassExW(&wc);
}

HWND InitMainWindow(HINSTANCE hInstance, int nCmdShow)
{
    HWND hwnd = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"MainWindow",
        L"Open Program",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1000,
        600,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return hwnd;
}*/



//ประกาศตัวแปร พวกข้อความ , ปุ่ม
HWND textTitleMenu, buttonShowCart, buttonAdd;
HWND textTitleCart, buttonBack_cart, buttonReciept_cart, borderTable;
HWND textTotal, headID, headName, headQty, headPrice, textEmpty, allTotal;
HWND receiptWindow = NULL;

PageManage pageManager; //ประกาศตัวแปร ระบบ page
CartSystem cartSystem; //ประกาศตัวแปร ระบบ cart
vector<CartTable> cartTable; //เอาตารางต่างๆไปไว้ใน vector
WNDPROC oldBorderProc;   // เก็บของเดิมไว้

int scrollPosition = 0;
int maxScroll = 0;

// forward declaration
LRESULT CALLBACK BorderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//callback ของใบเสร็จ
LRESULT CALLBACK ReceiptProc(HWND, UINT, WPARAM, LPARAM);



//ระบบ page-----------------------------------------------------------------------
PageManage::PageManage(){ //กำหนดค่าหน้าเป็นเริ่มต้น
    currentPage = menu_page;
}

void PageManage::setPage(int page){ //กำหนดค่าเปลี่ยนหน้า
    currentPage = page;
}

int PageManage::getPage(){ //ส่งค่าหน้าไป
    return currentPage;
}

//สร้างหน้า Cart
void startCartPage(HWND hwnd){ 
    //สร้าง text หัวเรื่อง
    textTitleCart = CreateWindowW(L"STATIC", L"CART PAGE", 
        WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE,
        0,0,300,50, 
        hwnd,NULL,NULL,NULL);

    //ขอบของกรอบ
    borderTable = CreateWindowExW(0,L"STATIC", NULL, 
        WS_CHILD|WS_VSCROLL|WS_CLIPCHILDREN|WS_VISIBLE, 
        100,190,1350,400, 
        hwnd,NULL,NULL,NULL);
    
    oldBorderProc = (WNDPROC)SetWindowLongPtr(borderTable, GWLP_WNDPROC, (LONG_PTR)BorderProc);

    //สร้างปุ่ม back
    buttonBack_cart = CreateWindowW(L"BUTTON",L"Back",
        WS_CHILD|WS_BORDER,
        0,0,200,50,
        hwnd,(HMENU) 2,NULL,NULL);

    //สร้างปุ่ม show reciept
    buttonReciept_cart = CreateWindowW(L"BUTTON",L"Show reciept",
        WS_CHILD|WS_BORDER,
        0,0,200,50,
        hwnd,(HMENU) 3,NULL,NULL);

    //แสดงหัวตาราง
    //ความกว้างแต่ละอัน
    int colID = 1333*15/100;
    int colName = 1333*40/100;
    int colQty = 1333*20/100;
    int colPrice = 1333 - (colID + colName + colQty);
    //ส่วนหัวตาราง
    headID = CreateWindowW(L"STATIC", L"ID", 
        WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE, 
        100,150,colID,40, 
        hwnd,NULL,NULL,NULL);
    headName= CreateWindowW(L"STATIC", L"NAME", 
        WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE, 
        100+colID,150,colName,40, 
        hwnd,NULL,NULL,NULL);
    headQty = CreateWindowW(L"STATIC", L"QUANTITY", 
        WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE, 
        100+colID+colName,150,colQty,40, 
        hwnd,NULL,NULL,NULL);
    headPrice = CreateWindowW(L"STATIC", L"PRICE", 
        WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE, 
        100+colID+colName+colQty,150,colPrice,40, 
        hwnd,NULL,NULL,NULL);

    //แสดงราคารวม
    allTotal = CreateWindowW(L"STATIC",L"TOTAL : ", 
        WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE, 
        100,590,1333,40, 
        hwnd,NULL,NULL,NULL);
}

//แสดงสิ่งต่างๆในหน้า cart
void showCartPage(HWND hwnd){ 
    //ซ่อนข้อความและปุ่มของหน้า menu
    ShowWindow(textTitleMenu, SW_HIDE);
    ShowWindow(buttonShowCart, SW_HIDE);
    ShowWindow(buttonAdd, SW_HIDE);

    //แสดงข้อความและปุ่มของหน้า cart
    ShowWindow(textTitleCart, SW_SHOW);
    ShowWindow(buttonBack_cart, SW_SHOW);
    ShowWindow(buttonReciept_cart, SW_SHOW);
    ShowWindow(borderTable, SW_SHOW);

    //แสดงส่วนหัวและท้ายตาราง
    ShowWindow(headID, SW_SHOW);
    ShowWindow(headName, SW_SHOW);
    ShowWindow(headQty, SW_SHOW);
    ShowWindow(headPrice, SW_SHOW);
    ShowWindow(allTotal, SW_SHOW);

    //set หน้าให้เป็น cart
    pageManager.setPage(pageManager.cart_page);

    scrollPosition = 0;
    SetScrollPos(borderTable, SB_VERT, scrollPosition, TRUE); //อันนี้มีการเปลี่ยนจาก hwnd เป็น borderTable เผื่อมีไรผิดแก้ที่นี่

    showCartItem(hwnd);
}

//ระบบแสดงหน้าใบเสร็จ
void showReceipt(HWND parent){

    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE);

    WNDCLASSEX wc;
    memset(&wc,0,sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = ReceiptProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255,255,255));
    wc.lpszClassName = L"ReceiptWindow";

    RegisterClassExW(&wc);

    int receiptWidth = 400;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // ให้สูงไม่เกินจอ
    int receiptHeight = 700;

    int x = (screenWidth - receiptWidth)/2;
    int y = (screenHeight - receiptHeight)/2;

    HWND receipt = CreateWindowExW(
        0,
        L"ReceiptWindow",
        L"Receipt",
        WS_CAPTION | WS_VSCROLL,
        x,y,
        receiptWidth,receiptHeight,
        parent,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(receipt, SW_SHOW);
}
//--------------------------------------------------------------------------------



//ระบบแสดงตาราง-------------------------------------------------------------------
void clearCartRows(){
    for(int i=0;i<cartTable.size();i++){
        DestroyWindow(cartTable[i].textId);
        DestroyWindow(cartTable[i].textName);
        DestroyWindow(cartTable[i].buttonMinus);
        DestroyWindow(cartTable[i].textQty);
        DestroyWindow(cartTable[i].buttonPlus);
        DestroyWindow(cartTable[i].textTotal);
    }
    cartTable.clear();
}

//แสดงตารางหน้า cart
void showCartItem(HWND hwnd){
    clearCartRows(); //เตลียร์ก่อน
    vector<CartItem> &cart = cartSystem.getCart(); //เอาของใน cart มา

    wchar_t numToChar[1000]; //ตัวแปรไว้เก็บข้อความความยาว 1000
    //ความกว้างตารางใน
    RECT borderRect;
    GetWindowRect(borderTable, &borderRect);
    int borderWidth = borderRect.right - borderRect.left; //ความกว้าง
    int scrollBarWidth = GetSystemMetrics(SM_CXVSCROLL);
    borderWidth -= scrollBarWidth;
    int ID = borderWidth*15/100;
    int Name = borderWidth*40/100;
    int Qty = borderWidth*20/100;
    int Price = borderWidth- (ID + Name + Qty);

    if(cart.size() == 0){ //ถ้าไม่มีของในตะกร้า
        textEmpty = CreateWindowW(L"STATIC", L"Cart is empty please select item.", 
            WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE, 
            0,200,borderWidth,40, 
            borderTable,NULL,NULL,NULL);
        SetWindowText(allTotal,L"TOTAL : 0.00");
        return;
    }

    for(int i = 0; i < cart.size(); i++){ //มีของในตะกร้าแสดงของ
        int y = (i * 40) - scrollPosition;
        CartTable row; //ประกาศตัวแปรของแถว
            
        //ID
        wsprintf(numToChar,L"%d",cart[i].item.id); //%d คือ int เราเอา id ที่เป็น int มาใส่เข้าไปในตัวแปรข้อความ
        row.textId = CreateWindowW(L"STATIC",numToChar, 
            WS_VISIBLE|WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE, 
            0,y,ID,40, 
            borderTable,NULL,NULL,NULL);
        //NAME
        row.textName = CreateWindowW(L"STATIC",cart[i].item.name.c_str(), //ใน struct ต้องเป็น wstring name สำหรับ win32
            WS_VISIBLE|WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE,       //และต่อท้ายด้วย .c_str() เพื่อคืนค่าเป็น pointer
            ID,y,Name,40, 
            borderTable,NULL,NULL,NULL);
        //button -
        row.buttonMinus = CreateWindowW(L"BUTTON",L"-",
            WS_VISIBLE|WS_CHILD|WS_BORDER|SS_CENTER,      
            ID+Name,y,40,40, 
            borderTable,(HMENU)(INT_PTR)(1000+cart[i].item.id),NULL,NULL);
        //QUANTITY
        wsprintf(numToChar,L"%d",cart[i].quantity); //%d คือ int เราเอา id ที่เป็น int มาใส่เข้าไปในตัวแปรข้อความ
        row.textQty = CreateWindowW(L"STATIC",numToChar, 
            WS_VISIBLE|WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE, 
            ID+Name+40,y,Qty-80,40, 
            borderTable,NULL,NULL,NULL);
        //button +
        row.buttonPlus = CreateWindowW(L"BUTTON",L"+",
            WS_VISIBLE|WS_CHILD|WS_BORDER|SS_CENTER,      
            ID+Name+40+Qty-80,y,40,40, 
            borderTable,(HMENU)(INT_PTR)(2000+cart[i].item.id),NULL,NULL);
        //Price
        double totalPrice = cart[i].item.price * cart[i].quantity;
        swprintf(numToChar,1000,L"%.2f",totalPrice);
        row.textTotal = CreateWindowW(L"STATIC",numToChar, 
            WS_VISIBLE|WS_CHILD|WS_BORDER|SS_CENTER|SS_CENTERIMAGE, 
            ID+Name+Qty,y,Price,40, 
            borderTable,NULL,NULL,NULL);
        //เอาไปใส่ในเวกเตอร์ตาราง
        cartTable.push_back(row);
    }
    //ราคารวม
    double total = cartSystem.calculate();
    swprintf(numToChar,1000,L"TOTAL : %.2f",total);
    SetWindowText(allTotal,numToChar);

    //การเลื่อน
    RECT clientRect;
    GetClientRect(borderTable, &clientRect);
    int clientHeight = clientRect.bottom;
    maxScroll = cart.size() * 40 - clientHeight;
    if(maxScroll < 0) maxScroll = 0;
    SCROLLINFO si;
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE|SIF_PAGE|SIF_POS;
    si.nMin = 0;
    si.nMax = cart.size() * 40;
    si.nPage = borderRect.bottom;
    si.nPos = scrollPosition;
    SetScrollInfo(borderTable, SB_VERT, &si, TRUE);
    if(maxScroll == 0){
        scrollPosition = 0;
        SetScrollPos(borderTable, SB_VERT, 0, TRUE);
    }
}
//--------------------------------------------------------------------------------



//ฟังก์ชันจัดการขนาดและตำแหน่ง--------------------------------------------------------
void resizeControl(HWND hwnd, int width, int height){
    int centerTitle_X = (width - 300)/2; //ทำให้ส่วนหัวอยู่ตรงกลาง

    if(pageManager.getPage() == pageManager.menu_page){ //ถ้าเป็นหน้า menu
        MoveWindow(textTitleMenu,centerTitle_X,50,300,50,TRUE); //กำหนดหัวเรื่องให้กลาง

        int button_showCart_x = width - 200 - 100;
        int button_showCart_y = height - 50 - 50;

        MoveWindow(buttonShowCart,(width-200)/2,button_showCart_y,200,50,TRUE);
        MoveWindow(buttonAdd,width-200-100,(height-50)/2,200,50,TRUE);
    }
    else if(pageManager.getPage() == pageManager.cart_page){ //ถ้าเป็นหน้า cart
        MoveWindow(textTitleCart,centerTitle_X,50,300,50,TRUE); //กำหนดหัวเรื่องให้กลาง

        int button_back_x = 100;
        int button_back_y = height - 50 - 50;

        MoveWindow(buttonBack_cart,button_back_x,button_back_y,200,50,TRUE);
        MoveWindow(buttonReciept_cart,width-200-100,button_back_y,200,50,TRUE);
    }
}
//--------------------------------------------------------------------------------



//สำหรับ cart ไว้แปลงปุ่มให้มันใช้งานได้--------------------------------------------------
LRESULT CALLBACK BorderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    if(msg == WM_COMMAND)
    {
        // ส่งต่อไปยัง main window
        SendMessage(GetParent(hwnd), WM_COMMAND, wParam, lParam);
        return 0;
    }

    return CallWindowProc(oldBorderProc, hwnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------------------



//สำหรับใบเสร็จเป็นหน้าต่างใหม่---------------------------------------------------------
int receiptScroll = 0;
int receiptMaxScroll = 0;

LRESULT CALLBACK ReceiptProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    static HWND exitButton;
    static vector<CartItem> receiptCart;

    switch(msg)
    {
        case WM_CREATE:
        {
            receiptCart = cartSystem.getCart();

            int y = 20;

            CreateWindowW(L"STATIC",L"Purchase Order",
                WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE|WS_BORDER,
                0,y,380,40,
                hwnd,NULL,NULL,NULL);

            y += 60;

            int colID = 50;
            int colName = 120;
            int colQty = 50;
            int colPrice = 70;
            int colTotal = 90;

            CreateWindowW(L"STATIC",L"ID",
                WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE|WS_BORDER,
                0,y,colID,30,hwnd,NULL,NULL,NULL);

            CreateWindowW(L"STATIC",L"Name",
                WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE|WS_BORDER,
                colID,y,colName,30,hwnd,NULL,NULL,NULL);

            CreateWindowW(L"STATIC",L"Qty",
                WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE|WS_BORDER,
                colID+colName,y,colQty,30,hwnd,NULL,NULL,NULL);

            CreateWindowW(L"STATIC",L"Price",
                WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE|WS_BORDER,
                colID+colName+colQty,y,colPrice,30,hwnd,NULL,NULL,NULL);

            CreateWindowW(L"STATIC",L"Total",
                WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE|WS_BORDER,
                colID+colName+colQty+colPrice,y,colTotal,30,hwnd,NULL,NULL,NULL);

            y += 40;

            wchar_t buffer[200];

            int i;
            for(i=0;i<receiptCart.size();i++)
            {
                int itemY = y + (i*35);

                wsprintf(buffer,L"%d",receiptCart[i].item.id);
                CreateWindowW(L"STATIC",buffer,
                    WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE,
                    0,itemY,colID,30,hwnd,NULL,NULL,NULL);

                CreateWindowW(L"STATIC",receiptCart[i].item.name.c_str(),
                    WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE,
                    colID,itemY,colName,30,hwnd,NULL,NULL,NULL);

                wsprintf(buffer,L"%d",receiptCart[i].quantity);
                CreateWindowW(L"STATIC",buffer,
                    WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE,
                    colID+colName,itemY,colQty,30,hwnd,NULL,NULL,NULL);

                swprintf(buffer,200,L"%.2f",receiptCart[i].item.price);
                CreateWindowW(L"STATIC",buffer,
                    WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE,
                    colID+colName+colQty,itemY,colPrice,30,hwnd,NULL,NULL,NULL);

                double total = receiptCart[i].item.price * receiptCart[i].quantity;
                swprintf(buffer,200,L"%.2f",total);
                CreateWindowW(L"STATIC",buffer,
                    WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE,
                    colID+colName+colQty+colPrice,itemY,colTotal,30,hwnd,NULL,NULL,NULL);
            }

            y += receiptCart.size()*35 + 20;

            swprintf(buffer,200,L"Grand Total : %.2f",cartSystem.calculate());
            CreateWindowW(L"STATIC",buffer,
                WS_VISIBLE|WS_CHILD|SS_CENTER|SS_CENTERIMAGE|WS_BORDER,
                0,y,380,40,hwnd,NULL,NULL,NULL);

            y += 60;

            exitButton = CreateWindowW(L"BUTTON",L"Exit",
                WS_VISIBLE|WS_CHILD|BS_CENTER|WS_BORDER,
                (380-150)/2,y,150,40,
                hwnd,(HMENU)1,NULL,NULL);

            y += 60;

            //คำนวณความสูง window
            RECT rect;
            GetClientRect(hwnd, &rect);
            int clientHeight = rect.bottom;
            
            //คำนวณ scroll สูงสุด
            receiptMaxScroll = y - clientHeight;
            if(receiptMaxScroll < 0) receiptMaxScroll = 0;
            
            //ตั้งค่า scroll bar
            SCROLLINFO si;
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
            si.nMin = 0;
            si.nMax = y;
            si.nPage = clientHeight;
            si.nPos = 0;
            
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

            break;
        }

        case WM_VSCROLL: {
            int oldScroll = receiptScroll;
            
            switch(LOWORD(wParam)){
                case SB_LINEUP: receiptScroll -= 40; break;
                case SB_LINEDOWN: receiptScroll += 40; break;
                case SB_THUMBTRACK: {
                    SCROLLINFO si;
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_TRACKPOS;
                    GetScrollInfo(hwnd, SB_VERT, &si);
                    receiptScroll = si.nTrackPos;
                    break;
                }
            }
            
            if(receiptScroll < 0) receiptScroll = 0;
            if(receiptScroll > receiptMaxScroll) receiptScroll = receiptMaxScroll;
            
            SetScrollPos(hwnd, SB_VERT, receiptScroll, TRUE);
            
            int delta = oldScroll - receiptScroll;
            ScrollWindow(hwnd, 0, delta, NULL, NULL);
            UpdateWindow(hwnd);
            
            break;
        }

        case WM_SYSCOMMAND: {
            if((wParam & 0xFFF0) == SC_CLOSE) return 0;
            break;
        }

        case WM_COMMAND:
        {
            if(LOWORD(wParam) == 1){
                PostQuitMessage(0);
            }
            break;
        }

        case WM_CLOSE:
            return 0;

        case WM_DESTROY:
            return 0;
    }

    return DefWindowProc(hwnd,msg,wParam,lParam);
}
//--------------------------------------------------------------------------------



/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
       
        case WM_CREATE: {
            startCartPage(hwnd);
            showMenuPage();
            break;
        }

        case WM_SIZE: { //เปลี่ยนขนาดและตำแหน่งของกล่องข้อความ , ปุ่ม
            RECT rect; //ประกาศตัวแปรของ struc RECT ที่เก็บพิกัดของ window
            GetClientRect(hwnd, &rect); //ฟังก์ชันเอาขนาดพื้นที่ด้านในของ window ไม่รวม title bar
            resizeControl(hwnd, rect.right, rect.bottom); //rect.right : ความกว้าง , rect.bottom : ความสูง
            break;
        }

        case WM_COMMAND: {

            switch (LOWORD(wParam)){
                case 1: { //ปุ่ม แสดงรถเข็น
                    showCartPage(hwnd);
                    RECT rect; //ประกาศตัวแปรของ struc RECT ที่เก็บพิกัดของ window
                    GetClientRect(hwnd, &rect); //ฟังก์ชันเอาขนาดพื้นที่ด้านในของ window ไม่รวม title bar
                    resizeControl(hwnd, rect.right, rect.bottom); //rect.right : ความกว้าง , rect.bottom : ความสูง
                    break;
                }
                case 2: { //ปุ่ม ย้อนหลับ
                    showMenuPage();
                    RECT rect; //ประกาศตัวแปรของ struc RECT ที่เก็บพิกัดของ window
                    GetClientRect(hwnd, &rect); //ฟังก์ชันเอาขนาดพื้นที่ด้านในของ window ไม่รวม title bar
                    resizeControl(hwnd, rect.right, rect.bottom); //rect.right : ความกว้าง , rect.bottom : ความสูง
                    break;
                }
                case 3: { //ปุ่ม โชว์ใบเสร็จ
                    if(cartSystem.getCart().empty()){
                        MessageBoxW(hwnd,L"---------------------------------------------\n\nYour cart is empty!!\n\nPlease select item before.\n\n---------------------------------------------", 
                            L"Warning!!", 
                            MB_OK);
                    }
                    else showReceipt(hwnd);
                    break;
                }
                case 99: { //ปุ่ม add

                    break;
                }
                default: {
                    int idButton = LOWORD(wParam);
                    if(idButton >= 1000 && idButton < 2000){ //ปุ่ม -
                        int id = idButton - 1000;
                        cartSystem.removeFromCart(id);
                        showCartItem(hwnd);
                    }
                    else if(idButton >= 2000){ //ปุ่ม +
                        int id = idButton - 2000;
                        vector<CartItem> &cart = cartSystem.getCart();
                        for(int i = 0; i < cart.size(); i++){
                            if(cart[i].item.id == id){
                                cartSystem.addToCart(cart[i].item);
                                break;
                            }
                        }
                        showCartItem(hwnd);
                    }
                    break;
                }
            }

            break;
        }

        //การเลื่อนจอ
        case WM_VSCROLL: {
            if((HWND)lParam == borderTable){
                switch(LOWORD(wParam)){
                    case SB_LINEUP: {
                        scrollPosition -= 40;
                        break;
                    }
                    case SB_LINEDOWN:{
                        scrollPosition += 40;
                        break;
                    }
                    case SB_THUMBTRACK:{
                        SCROLLINFO si;
                        si.cbSize = sizeof(si);
                        si.fMask = SIF_TRACKPOS;
                        GetScrollInfo(borderTable, SB_VERT, &si);
                        scrollPosition = si.nTrackPos;
                        break;
                    }
                }
                
                if(scrollPosition < 0) scrollPosition = 0;
                if(scrollPosition > maxScroll) scrollPosition = maxScroll;
                
                SetScrollPos(borderTable,SB_VERT,scrollPosition,TRUE);
                showCartItem(hwnd);
            }
            break;
        }

        case WM_MOUSEWHEEL: {
            int delta = GET_WHEEL_DELTA_WPARAM(wParam);

            if(delta > 0) scrollPosition -= 40;
            else scrollPosition += 40;

            if(scrollPosition < 0) scrollPosition = 0;
            if(scrollPosition > maxScroll) scrollPosition = maxScroll;

            SetScrollPos(borderTable, SB_VERT, scrollPosition, TRUE);
            showCartItem(hwnd);
            break;
        }

        /* Upon destruction, tell the main thread to stop */
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
       
        /* All other messages (a lot of them) are processed using default procedures */
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}



// The 'main' function of Win32 GUI programs: this is where execution starts
/*
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc; // A properties struct of our window
    HWND hwnd; // A 'HANDLE', hence the H, or a pointer to our window
    MSG msg; // A temporary location for all messages

    // zero out the struct and set the stuff we want to modify
    memset(&wc,0,sizeof(wc));
    wc.cbSize    = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc; // This is where we will send messages to 
    wc.hInstance     = hInstance;
    wc.hCursor   = LoadCursor(NULL, IDC_ARROW);
   
    // White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it 
    wc.hbrBackground = CreateSolidBrush(RGB(150,175,220));
    wc.lpszClassName = L"WindowClass";
    wc.hIcon     = LoadIcon(NULL, IDI_APPLICATION); // Load a standard icon 
    wc.hIconSm   = LoadIcon(NULL, IDI_APPLICATION); // use the name "A" to use the project icon

    if(!RegisterClassExW(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!",L"Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowExW(WS_EX_CLIENTEDGE,L"WindowClass",L"Open Program", 
        WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, // x 
        CW_USEDEFAULT, // y
        800, // width 
        450, // height 
        NULL,NULL,hInstance,NULL);

    ShowWindow(hwnd, SW_MAXIMIZE);
    UpdateWindow(hwnd);

    if(hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!",L"Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    
        // This is the heart of our program where all input is processed and
        // sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
        // this loop will not produce unreasonably high CPU usage
    
    while(GetMessage(&msg, NULL, 0, 0) > 0) { // If no error is received... 
        TranslateMessage(&msg); // Translate key codes to chars if present 
        DispatchMessage(&msg); // Send it to WndProc 
    }
    return msg.wParam;
}
*/