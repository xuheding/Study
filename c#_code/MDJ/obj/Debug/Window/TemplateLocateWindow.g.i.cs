#pragma checksum "..\..\..\Window\TemplateLocateWindow.xaml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "75C62ADB2BE3A252FB128672CBF2199DCCF1F883"
//------------------------------------------------------------------------------
// <auto-generated>
//     此代码由工具生成。
//     运行时版本:4.0.30319.42000
//
//     对此文件的更改可能会导致不正确的行为，并且如果
//     重新生成代码，这些更改将会丢失。
// </auto-generated>
//------------------------------------------------------------------------------

using MDJ;
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;
using sdl;


namespace MDJ {
    
    
    /// <summary>
    /// TemplateLocateWindow
    /// </summary>
    public partial class TemplateLocateWindow : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 11 "..\..\..\Window\TemplateLocateWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal sdl.ImageVisual imgVisual;
        
        #line default
        #line hidden
        
        
        #line 17 "..\..\..\Window\TemplateLocateWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Media.ScaleTransform imgScale;
        
        #line default
        #line hidden
        
        
        #line 18 "..\..\..\Window\TemplateLocateWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Media.TranslateTransform imgTransform;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/MDJ;component/window/templatelocatewindow.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\Window\TemplateLocateWindow.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.imgVisual = ((sdl.ImageVisual)(target));
            
            #line 12 "..\..\..\Window\TemplateLocateWindow.xaml"
            this.imgVisual.MouseRightButtonDown += new System.Windows.Input.MouseButtonEventHandler(this.onImageMouseRightDown);
            
            #line default
            #line hidden
            
            #line 12 "..\..\..\Window\TemplateLocateWindow.xaml"
            this.imgVisual.MouseRightButtonUp += new System.Windows.Input.MouseButtonEventHandler(this.onImageMouseRightUp);
            
            #line default
            #line hidden
            
            #line 13 "..\..\..\Window\TemplateLocateWindow.xaml"
            this.imgVisual.MouseLeftButtonDown += new System.Windows.Input.MouseButtonEventHandler(this.onImageMouseLeftDown);
            
            #line default
            #line hidden
            
            #line 13 "..\..\..\Window\TemplateLocateWindow.xaml"
            this.imgVisual.MouseLeftButtonUp += new System.Windows.Input.MouseButtonEventHandler(this.onImageMouseLeftUp);
            
            #line default
            #line hidden
            
            #line 14 "..\..\..\Window\TemplateLocateWindow.xaml"
            this.imgVisual.MouseLeave += new System.Windows.Input.MouseEventHandler(this.onImageMouseLeave);
            
            #line default
            #line hidden
            
            #line 14 "..\..\..\Window\TemplateLocateWindow.xaml"
            this.imgVisual.MouseMove += new System.Windows.Input.MouseEventHandler(this.onImageMouseMove);
            
            #line default
            #line hidden
            
            #line 14 "..\..\..\Window\TemplateLocateWindow.xaml"
            this.imgVisual.MouseWheel += new System.Windows.Input.MouseWheelEventHandler(this.onImageMouseWheel);
            
            #line default
            #line hidden
            return;
            case 2:
            this.imgScale = ((System.Windows.Media.ScaleTransform)(target));
            return;
            case 3:
            this.imgTransform = ((System.Windows.Media.TranslateTransform)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

