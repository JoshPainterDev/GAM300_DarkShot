using UnityEngine;
using System.Collections;
using Valve.VR;
public class RightControllerInput : MonoBehaviour {

    private SteamVR_TrackedController device;
    public bool isArrowAlive;

    private GameObject currentArrow;
    public GameObject arrowPrefab;
	// Use this for initialization
	void Start () {
        device = GetComponent<SteamVR_TrackedController>();
        device.TriggerClicked += SpawnArrowToRightHand;
        isArrowAlive = false;
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    void SpawnArrowToRightHand()
    {
        if(isArrowAlive == false)
        {
            // spawn arrow then parent it
            currentArrow = Instantiate(arrowPrefab);

        }
        Debug.Log("Trigger has been pressed");
    }
}
