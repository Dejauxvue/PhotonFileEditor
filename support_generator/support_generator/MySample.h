#pragma once

namespace supportgenerator
{
	using namespace Urho;
	using namespace Urho::Gui;
	public ref class MySample : public Urho::Application
	{
	public:
		MySample(ApplicationOptions^ options) :Urho::Application(options) { }

	protected:

		void Start(void) override
		{
			CreateScene();
			Input->KeyDown += gcnew System::Action<KeyDownEventArgs>(this, &MySample::KeyDownCallback);
		}

	private: System::Void KeyDownCallback(KeyDownEventArgs e) {
		if (e.Key == Key::Esc)
			Exit();
	}

		   void CreateScene(void)
		   {
			   // UI text
			   Urho::Gui::Text^ helloText = gcnew Urho::Gui::Text();
			   helloText->Value = "Hello World from MySample";
			   helloText->HorizontalAlignment = Urho::Gui::HorizontalAlignment::Center;
			   helloText->VerticalAlignment = Urho::Gui::VerticalAlignment::Center;
			   helloText->SetColor(Urho::Color(0.f, 1.f, 1.f, 1.f));
			   helloText->SetFont("Fonts/Anonymous Pro.ttf", 30);
			   UI->Root->AddChild(helloText);

			   //// Create a top-level scene, must add the Octree
			   //// to visualize any 3D content.
			   Urho::Scene^ scene = gcnew Urho::Scene();
			   //scene->CreateComponent<Urho::Octree::typeid>();
			   //// Box
			   //Node boxNode = scene.CreateChild();
			   //boxNode.Position = new Vector3(0, 0, 5);
			   //boxNode.Rotation = new Quaternion(60, 0, 30);
			   //boxNode.SetScale(0f);
			   //StaticModel modelObject = boxNode.CreateComponent<StaticModel>();
			   //modelObject.Model = ResourceCache.GetModel("Models/Box.mdl");
			   //// Light
			   //Node lightNode = scene.CreateChild(name: "light");
			   //lightNode.SetDirection(new Vector3(0.6f, -1.0f, 0.8f));
			   //lightNode.CreateComponent<Light>();
			   //// Camera
			   //Node cameraNode = scene.CreateChild(name: "camera");
			   //Camera camera = cameraNode.CreateComponent<Camera>();
			   //// Viewport
			   //Renderer.SetViewport(0, new Viewport(scene, camera, null));
			   //// Perform some actions
			   //await boxNode.RunActionsAsync(
			   //    new EaseBounceOut(new ScaleTo(duration: 1f, scale : 1)));
			   //await boxNode.RunActionsAsync(
			   //    new RepeatForever(new RotateBy(duration: 1,
			   //        deltaAngleX : 90, deltaAngleY : 0, deltaAngleZ : 0)));
		   }
	};
}
