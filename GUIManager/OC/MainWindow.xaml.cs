using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System;
using System.Runtime.InteropServices;

using OcWrapper;

static class Constants
{
    public const double POINT_SIZE = 5;
    public const double AREA_SIZE = 200;
    public const double SHOOT_SIZE = 20;
}


namespace OC
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        OcWrapperClass wrapper;
        public MainWindow()
        {
            InitializeComponent();

            //string imagePath = "/map.jpg";

            //// 이미지를 로드하고 Image 엘리먼트에 할당합니다.
            //BitmapImage bitmap = new BitmapImage();
            //bitmap.BeginInit();
            //bitmap.UriSource = new Uri(imagePath, UriKind.RelativeOrAbsolute);
            //bitmap.EndInit();
            //Image image = new Image();
            //image.Source = bitmap;

            //// Canvas에 이미지를 배치합니다. (좌표 설정)
            //Canvas.SetLeft(image, 250);  // X 좌표
            //Canvas.SetTop(image, 250);   // Y 좌표
            //cvMap.Children.Add(image);

            DrawPoint(40, 40, 1);
            DrawPoint(40, 50, 1);
            DrawPoint(40, 60, 1);

            wrapper = new OcWrapperClass();
            //객채 생성
            wrapper.MyEvent_AdrsTgtInfo += new OcWrapperClass.MyEventHandler_AdrsTgtInfo(rcvTarget);
            //메소드 이벤트 설정 - do함수 - 실제 실행 함수 설정

            //wrapper.RunComm();
        }
        
        public void doSomthing(string message) //실제 작업 연결
        {
            // UI 스레드로 작업 요청할 때는 invoke 사용
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
                delegate
                {
                    labAtsCurX.Content = 5;
                }));
        }//실제 동작 구현 함수 - 동작별로 설정

        private void rcvTarget(double x, double y)
        {
            DrawPoint(x, y, 1);
        }
        private void rcvMissile(double x, double y)
        {
            DrawPoint(x, y, 2);
        }

        private void DrawPoint(double x, double y, int flag) // 1 : ATS, 2 : MSL, 3: Other
        {

            Ellipse ellipse = new Ellipse //elipse 좌표 수신하면 넘겨주는게 에러 -> 수신확인 ok
            {
                Width = Constants.POINT_SIZE, // 점의 너비
                Height = Constants.POINT_SIZE // 점의 높이
            };

            if (flag == 1) { ellipse.Fill = Brushes.Red; }
            else if (flag == 2) { ellipse.Fill = Brushes.Blue; }
            else if (flag == 3) { ellipse.Fill = Brushes.Black; }

            // Canvas에 점을 추가합니다.
            Canvas.SetLeft(ellipse, x);
            Canvas.SetTop(ellipse, y);
            cvMap.Children.Add(ellipse);
        }

        private void DrawArea(double x, double y, int flag) // 1 : MSL, 2 : LCS, 3: ADRS
        {
            double radius = Constants.AREA_SIZE;

            Ellipse ellipse = new Ellipse
            {
                Width = 2 * radius, // 원의 지름
                Height = 2 * radius, // 원의 지름
                StrokeThickness = 2 // 원의 테두리 두께
            };

            if (flag == 1) { ellipse.Stroke = Brushes.Red; }
            else if (flag == 2) { ellipse.Stroke = Brushes.Blue; }
            else if (flag == 3) { ellipse.Stroke = Brushes.Black; }

            // Canvas에 원을 추가합니다.
            Canvas.SetLeft(ellipse, x - radius);
            Canvas.SetTop(ellipse, y - radius);
            cvMap.Children.Add(ellipse);
        }

        private void setMslLoc(double curX, double curY)
        {
            labMslCurX.Content = curX;
            labMslCurY.Content = curY;
        }

        private void mapClear()
        {
            cvMap.Children.Clear();
        }

        private void setAtsLoc(double curX, double curY)
        {
            labAtsCurX.Content = curX;
            labAtsCurY.Content = curY;
        }

        private void makeLog(byte[] msg)
        {

        }
        private void btnSendScenario_Click(object sender, RoutedEventArgs e)
        {
            double lcsX = double.Parse(txbLcsX.Text);
            double lcsY = double.Parse(txbLcsY.Text);
            double mslSpeed = double.Parse(txbMslSpeed.Text);
            double adrsX = double.Parse(txbAdrsX.Text);
            double adrsY = double.Parse(txbAdrsY.Text);
            double atsStartX = double.Parse(txbAtsStartX.Text);
            double atsStartY = double.Parse(txbAtsStartY.Text);
            double atsEndX = double.Parse(txbAtsEndY.Text);
            double atsEndY = double.Parse(txbAtsEndY.Text);
            double atsSpeed = double.Parse(txbAtsSpeed.Text);

            //send추가
        }

        private void checkShootDown(double atsX, double atsY, double mslX, double mslY)
        {
            double deltaX = atsX - mslX;
            double deltaY = atsY - mslY;
            double distance = Math.Sqrt(deltaX * deltaX + deltaY * deltaY);

            if (distance <= Constants.SHOOT_SIZE)
            {
                //send shoot event
            }
        }

        private void btnStartSim_Click(object sender, RoutedEventArgs e)
        {
            //모의 시작 메시지 전송
        }

        private void btnEndSim_Click(object sender, RoutedEventArgs e)
        {
            //모의 종료 메시지 전송

            mapClear();
        }

        private void btnFire_Click(object sender, RoutedEventArgs e)
        {
            //발사명령 메시지 전송
        }

    }
}



