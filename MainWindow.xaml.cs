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

using System.Text.RegularExpressions;

using OcWrapper;


static class Constants
{
    public const double POINT_SIZE = 6.0;
    public const double AREA_SIZE = 200.0;
    public const double SHOOT_SIZE = 10.0;
}


namespace OC
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        OcWrapperClass wrapper;
        int fireFlag = 0;
        int btnCnt = 0;
        int AtsConStat = 1;
        int MssConStat = 1;
        int LcsConStat = 1;
        int AdrsConStat = 1;

        public MainWindow()
        {
            InitializeComponent();

            wrapper = new OcWrapperClass();
            //객채 생성
            wrapper.MyEvent_AdrsTgtInfo += new OcWrapperClass.MyEventHandler_AdrsTgtInfo(rcvTarget);
            wrapper.MyEvent_AdrsRadarInfo += new OcWrapperClass.MyEventHandler_AdrsRadarInfo(rcvAdrsInfo);
            wrapper.MyEvent_LcsLauncherInfo += new OcWrapperClass.MyEventHandler_LcsLauncherInfo(rcvLcsInfo);
            wrapper.MyEvent_MssMissileInfo += new OcWrapperClass.MyEventHandler_MssMissileInfo(rcvMissile);
            wrapper.MyEvent_AtsConnection += new OcWrapperClass.MyEventHandler_AtsConnection(rcvAtsConnection);
            wrapper.MyEvent_MssConnection += new OcWrapperClass.MyEventHandler_MssConnection(rcvMssConnection);
            wrapper.MyEvent_LcsConnection += new OcWrapperClass.MyEventHandler_LcsConnection(rcvLcsConnection);
            wrapper.MyEvent_AdrsConnection += new OcWrapperClass.MyEventHandler_AdrsConnection(rcvAdrsConnection);
            //메소드 이벤트 설정 - do함수 - 실제 실행 함수 설정

            btnFire.IsEnabled = false;
            btnStartSim.IsEnabled = false;
            btnSendScenario.IsEnabled = false;
            btnEndSim.IsEnabled = false;

        }

        private void CheckAllConn()
        {
            if(AdrsConStat == 1 && LcsConStat == 1 && AtsConStat == 1 && MssConStat == 1)
            {
                Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
               delegate
               {
               labMode.Content = "대기 모드";
                   // 배포버튼 활성
                   btnStartSim.IsEnabled = true;
                   btnSendScenario.IsEnabled = true;
                   btnEndSim.IsEnabled = false;
                   var str2 = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 대기 모드 ]";
                lstLog.Items.Add(str2);
                   if(int.Parse(txbMslCnt.Text) == 0) { txbMslCnt.IsEnabled = false; }
                labMode.Background = Brushes.LightYellow;
               }));
            }

        }

        private void rcvAtsConnection(int val)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                if (val == 1) // 통신 확인
                {
                    AtsConStat = 1;
                    CheckAllConn();
                    imgAtsDiscon.Visibility = Visibility.Hidden;
                    imgAtsConn.Visibility = Visibility.Visible;
                }
                else
                {
                    AtsConStat = 0;
                    imgAtsDiscon.Visibility = Visibility.Visible;
                    imgAtsConn.Visibility = Visibility.Hidden;
                }
            }));

        }

        private void rcvLcsConnection(int val)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                if (val == 1)// 통신 확인
                {
                    LcsConStat = 1;
                    CheckAllConn();
                    imgLcsDiscon.Visibility = Visibility.Hidden;
                    imgLcsConn.Visibility = Visibility.Visible;
                }
                else
                {
                    LcsConStat = 0;
                    imgLcsDiscon.Visibility = Visibility.Visible;
                    imgLcsConn.Visibility = Visibility.Hidden;
                }
            }));

        }

        private void rcvMssConnection(int val)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                if (val == 1)// 통신 확인
                {
                    MssConStat = 1;
                    CheckAllConn();
                    imgMssDiscon.Visibility = Visibility.Hidden;
                    imgMssConn.Visibility = Visibility.Visible;
                }
                else
                {
                    MssConStat = 0;
                    imgMssDiscon.Visibility = Visibility.Visible;
                    imgMssConn.Visibility = Visibility.Hidden;
                }
            }));

        }

        private void rcvAdrsConnection(int val)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
              if (val == 1)// 통신 확인
                {
                    AdrsConStat = 1;
                    CheckAllConn();
                    imgAdrsDiscon.Visibility = Visibility.Hidden;
                    imgAdrsConn.Visibility = Visibility.Visible;
                }
                else
                {
                    AdrsConStat = 0;
                    imgAtsDiscon.Visibility = Visibility.Visible;
                    imgAtsConn.Visibility = Visibility.Hidden;
                }
            }));
  
        }

        private void rcvTarget(double x, double y, byte fireBtnOnOffFlag)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                if(fireBtnOnOffFlag == 1) // 적 식별 여부
                {
                    DrawPoint(x, y, 1);
                }
                else
                {
                    DrawPoint(x, y, 5);
                }
                
                setAtsLoc(x, y);

                if(fireFlag == 1)
                {
                    btnFire.Background = new SolidColorBrush(Colors.White);
                    btnFire.IsEnabled = false;
                }

                else if (fireBtnOnOffFlag == 1 && fireFlag == 0) // on
                {
                    btnFire.IsEnabled = true;
                    if (btnCnt % 2 == 0)
                    {

                        btnFire.Background = new SolidColorBrush(Colors.Red);
                    }
                    else
                    {
                        btnFire.Background = new SolidColorBrush(Colors.Gray);
                    }
                    btnCnt++;
                }
                else //off
                {
                    btnFire.IsEnabled = false;
                    btnFire.Background = new SolidColorBrush(Colors.DarkGray);
                    btnCnt = 0;
                }

                var str = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 공중 위협 좌표 수신 ]";
                lstLog.Items.Add(str);

                if (fireFlag == 1)
                {
                    wrapper.SendTgtInfoToMss(x, y); //발사명령 flag 생성
                    var str2 = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 공중 위협 좌표 송신 ]";
                    lstLog.Items.Add(str2);
                }
                checkShootDown(double.Parse(labAtsCurX.Content.ToString()), double.Parse(labAtsCurY.Content.ToString()),
                    double.Parse(labMslCurX.Content.ToString()), double.Parse(labMslCurY.Content.ToString()));

            }));
        }


        private void rcvMissile(double x, double y)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                DrawPoint(x, y, 2);
               //DrawArea(x, y, 1);
                setMslLoc(x, y);

                double AtsX = double.Parse(labAtsCurX.Content.ToString());
                double AtsY = double.Parse(labAtsCurY.Content.ToString());
                double MslX = double.Parse(labMslCurX.Content.ToString());
                double MslY = double.Parse(labMslCurY.Content.ToString());
          
                var str = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 미사일 좌표 수신 ]";
                lstLog.Items.Add(str);

            }));
        }

        private void rcvLcsInfo(double x, double y, byte missileCnt)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                DrawPoint(x, y, 4);
                txbMslCnt.Text = missileCnt.ToString();

                var str = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 발사대 위치 수신 ]";
                lstLog.Items.Add(str);
            }));
        }

        private void rcvAdrsInfo(double x, double y)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                DrawPoint(x, y, 3);
                DrawArea(x, y, 3);
                var str = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 레이더 위치 수신 ]";
                lstLog.Items.Add(str);

            }));
        }

        private void DrawPoint(double x, double y, int flag) // 1:ATS, 2:MSL, 3:ADRS, 4:LCS, 5: nonT
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                Ellipse ellipse = new Ellipse //elipse 좌표 수신하면 넘겨주는게 에러 -> 수신확인 ok
                {
                    Width = Constants.POINT_SIZE, // 점의 너비
                    Height = Constants.POINT_SIZE // 점의 높이
                };

                if (flag == 1) { ellipse.Fill = Brushes.Red; }
                else if (flag == 2) { ellipse.Fill = Brushes.Blue; }
                else if (flag == 3) { ellipse.Fill = Brushes.Black; }
                else if (flag == 4) { ellipse.Fill = Brushes.Green; }
                else if (flag == 5) { ellipse.Fill = Brushes.DarkOrange; }


                // Canvas에 점을 추가합니다.
                Canvas.SetLeft(ellipse, x);
                Canvas.SetTop(ellipse, y);
                cvMap.Children.Add(ellipse);
            }));
        }

        private void DrawArea(double x, double y, int flag) // 1 : MSL, 2 : LCS, 3: ADRS
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                double radius = Constants.AREA_SIZE;

                Ellipse ellipse = new Ellipse
                {
                    Width = 2 * radius, // 원의 지름
                    Height = 2 * radius, // 원의 지름
                    StrokeThickness = 2 // 원의 테두리 두께
                };

                if (flag == 1) { ellipse.Stroke = Brushes.Blue; }
                else if (flag == 2) { ellipse.Stroke = Brushes.Black; }
                else if (flag == 3) { ellipse.Stroke = Brushes.Red; }

                // Canvas에 원을 추가합니다.
                Canvas.SetLeft(ellipse, x - radius);
                Canvas.SetTop(ellipse, y - radius);
                cvMap.Children.Add(ellipse);
            }));
        }

        private void setMslLoc(double curX, double curY)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                labMslCurX.Content = curX.ToString("#.####");
                labMslCurY.Content = curY.ToString("#.####");

            }));
        }

        private void mapClear()
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                cvMap.Children.Clear();
                labAtsCurX.Content = "0.0000";
                labAtsCurY.Content = "0.0000";
                labMslCurX.Content = "0.0000";
                labMslCurX.Content = "0.0000";
            }));
        }

        private void setAtsLoc(double curX, double curY)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                labAtsCurX.Content = curX.ToString("#.####");
                labAtsCurY.Content = curY.ToString("#.####");
            }));
        }


        private void btnSendScenario_Click(object sender, RoutedEventArgs e)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                double lcsX = double.Parse(txbLcsX.Text);
                double lcsY = double.Parse(txbLcsY.Text);
                double mslSpeed = double.Parse(txbMslSpeed.Text);
                double adrsX = double.Parse(txbAdrsX.Text);
                double adrsY = double.Parse(txbAdrsY.Text);
                double atsStartX = double.Parse(txbAtsStartX.Text);
                double atsStartY = double.Parse(txbAtsStartY.Text);
                double atsEndX = double.Parse(txbAtsEndX.Text);
                double atsEndY = double.Parse(txbAtsEndY.Text);
                double atsSpeed = double.Parse(txbAtsSpeed.Text);
                byte lcsMissileCnt = byte.Parse(txbMslCnt.Text);

                wrapper.SendScenario((uint)mslSpeed, atsStartX, atsStartY, atsEndX, atsEndY, (uint)atsSpeed, lcsX, lcsY, adrsX, adrsY, lcsMissileCnt);

                var str = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 시나리오 배포 ]";
                lstLog.Items.Add(str);
            }));

            //makelog 추가
        }

        private void checkShootDown(double atsX, double atsY, double mslX, double mslY)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                double deltaX = atsX - mslX;
                double deltaY = atsY - mslY;
                double distance = Math.Sqrt((deltaX * deltaX) + (deltaY * deltaY));

                if ((Math.Abs(atsX - double.Parse(txbAtsEndX.Text)) <= 10.0) && (Math.Abs(atsY - double.Parse(txbAtsEndY.Text)) <= 10.0))
                {
                    wrapper.SendShotResult(2);
                    fireFlag = 0;
                    MessageBox.Show("실패", "격추 결과", MessageBoxButton.OK, MessageBoxImage.Error);

                    var str = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 격추 실패 이벤트 송신 ]";
                    lstLog.Items.Add(str);
                }
                else //목표점 미도달시
                {
                    if (distance <= Constants.SHOOT_SIZE) // 격추시
                    {
                        wrapper.SendShotResult(1); // 격추이벤트 전송
                        fireFlag = 0;
                        MessageBox.Show("성공", "격추 결과", MessageBoxButton.OK, MessageBoxImage.Information);

                        var str = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 격추 성공 이벤트 송신 ]";
                        lstLog.Items.Add(str);
                    }
                }

            }));
        }

        private void btnStartSim_Click(object sender, RoutedEventArgs e)
        {
            wrapper.SendSimulationStartStop(1);

            var str = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 모의 시작 이벤트 송신 ]";
            lstLog.Items.Add(str);
            var str2 = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 모의 모드 ]";
            lstLog.Items.Add(str2);
            labMode.Content = "모의 모드";
            labMode.Background = Brushes.LightGreen;
            btnSendScenario.IsEnabled = false;
            btnStartSim.IsEnabled = false;
            btnEndSim.IsEnabled = true;

        }

        private void btnEndSim_Click(object sender, RoutedEventArgs e)
        {
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(
            delegate
            {
                mapClear();
            }));
            wrapper.SendSimulationStartStop(2);
            fireFlag = 0;

            var str = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 모의 종료 이벤트 송신 ]";
            lstLog.Items.Add(str);
            var str2 = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 대기 모드 ]";
            lstLog.Items.Add(str2);
            labMode.Content = "대기 모드";
            labMode.Background = Brushes.LightYellow;
            btnSendScenario.IsEnabled = true;
            btnEndSim.IsEnabled = false;

            if(int.Parse(txbMslCnt.Text) == 0) // 0발 이하 모의 
            {
                btnStartSim.IsEnabled = false;
            }
            else                              //발사가능 시 모의 시작 활성화
            {
                btnStartSim.IsEnabled = true;
            }
        }

        private void btnFire_Click(object sender, RoutedEventArgs e)
        {
            wrapper.SendFireCmd();
            fireFlag = 1;
            var str = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss ") + "[ 발사 명령 이벤트 송신 ]";
            lstLog.Items.Add(str);
        }

        private void txbLcsX_textChange(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("^[0-9.]*$");
            e.Handled = !regex.IsMatch(e.Text);
        }

        private void txbAdrsY_textchanged(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("^[0-9.]*$");
            e.Handled = !regex.IsMatch(e.Text);
        }

        private void txbAtsStartX_textchanged(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("^[0-9.]*$");
            e.Handled = !regex.IsMatch(e.Text);
        }
    }
}



